#include <iostream>
#include <unistd.h>
#ifdef HERMES_PLATFORM_LINUX
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <map>
#include <pwd.h>
#include <string>
#include <sys/utsname.h>
#include <variant>

#include "Log.h"
#include "OS.h"

namespace Hermes {
std::string_view LinuxAPI::GetVariant() {
    if (m_Variant.empty())
        ParseUtsname();
    return m_Variant;
}

std::string_view LinuxAPI::GetVersion() {
    if (m_Version.empty())
        ParseUtsname();
    return m_Version;
}

void LinuxAPI::ParseUtsname() {
    // We will prioritize /etc/os-release info, if available
    utsname NAME;
    uname(&NAME);
    m_Variant = NAME.nodename;
    m_Version = NAME.release;

    // TODO: PARSE /etc/os-release "NAME" and "VERSION"
}

void GetDirectoryEnv(std::string &s, const char *envVar, const char *name) {
    auto var = std::getenv(envVar);
    if (var == NULL)
        return;

    s = var;
}

void GetDirectory(std::string &s, const char *envVar, const char *name,
                  const std::map<std::string, std::string> &xdgUserDirs) {
    // Enviroment variables are prioritized
    GetDirectoryEnv(s, envVar, name);
    if (s.empty()) {
        auto it = xdgUserDirs.find(envVar);
        if (it != xdgUserDirs.end())
            s = it->second;
        else {
            WARN("No {} directory!", name);
            return;
        }
    }
    TRACE("{} directory: {}", name, s);
}

void FindHomeBackup(std::string &s) {
    s = getpwuid(getuid())->pw_dir;
    TRACE("HOME variable not set! Using backup home folder method, found: {}",
          s);
}

void FindConfigBackup(std::string &s, std::string_view pathHome) {
    auto configFolder = std::filesystem::path(pathHome) / ".config/";
    if (!std::filesystem::exists(configFolder)) {
        WARN("XDG_CONFIG_HOME not set and backup method found no viable "
             "folder!");
        return;
    }

    s = configFolder.string();
    TRACE("XDG_CONFIG_HOME variable not set! Using backup method, found: {}",
          s);
}

std::map<std::string, std::string> ParseXDGDirs(std::string_view configFolder,
                                                const std::string &homeFolder) {
    std::filesystem::path userDirsFile =
        std::filesystem::path(configFolder) / "user-dirs.dirs";
    if (!std::filesystem::exists(userDirsFile)) {
        TRACE("Skipping ParseXDGDirs. File not found: {}",
              userDirsFile.string());
        return {};
    }

    /* The format as specified from my user-dirs.dirs file
# This file is written by xdg-user-dirs-update
# If you want to change or add directories, just edit the line you're
# interested in. All local changes will be retained on the next run.
# Format is XDG_xxx_DIR="$HOME/yyy", where yyy is a shell-escaped
# homedir-relative path, or XDG_xxx_DIR="/yyy", where /yyy is an
# absolute path. No other format is supported.
    */

    std::map<std::string, std::string> vars;
    std::ifstream infile(userDirsFile);
    std::string line;
    while (std::getline(infile, line)) {
        if (line.starts_with('#'))
            continue;

        auto equals = line.find_first_of('=');
        if (equals == std::variant_npos) {
            WARN("Invalid xdg-user-dirs line: \"{}\"", line);
            continue;
        }

        // Finding the name of format XDG_xxx_DIR
        std::string name = line.substr(0, equals);
        if (!name.starts_with("XDG_") || !name.ends_with("_DIR")) {
            WARN("Invalid xdg-user-dirs variable name: \"{}\"", name);
            continue;
        }

        // Reading the value, stripping the quotation marks
        std::string value = line.substr(equals + 2, line.length() - equals - 3);
        if (value.starts_with("/"))
            vars[name] = value;
        else if (value.starts_with("$HOME"))
            vars[name] = homeFolder + value.substr(5, value.length() - 5);
        else {
            WARN("Invalid xdg-user-dirs variable value: \"{}\"", value);
            continue;
        }
    };
    infile.close();

    TRACE("Read xdg-user-dirs and found {} values", vars.size());
    return vars;
}

LinuxAPI::LinuxAPI() {
    // Get essential paths
    GetDirectoryEnv(m_PathHome, "HOME", "Home");
    if (m_PathHome.empty())
        FindHomeBackup(m_PathHome);
    TRACE("Home directory: {}", m_PathHome);

    GetDirectoryEnv(m_PathConfig, "XDG_CONFIG_HOME", "Config");
    if (m_PathConfig
            .empty()) // Since the config dir is used to check for xdg-user-dirs
                      // file, we make an extra effort to find it
        FindConfigBackup(m_PathConfig, m_PathHome);
    TRACE("Config directory: {}", m_PathConfig);

    // Parse xdg user dirs, this is used as a fallback for the next folders
    const auto xdgUserDirs = ParseXDGDirs(m_PathConfig, m_PathHome);

    // Get user dirs
    GetDirectory(m_PathDesktop, "XDG_DESKTOP_DIR", "Desktop", xdgUserDirs);
    GetDirectory(m_PathDocuments, "XDG_DOCUMENTS_DIR", "Documents",
                 xdgUserDirs);
    GetDirectory(m_PathDownloads, "XDG_DOWNLOAD_DIR", "Downloads", xdgUserDirs);
    GetDirectory(m_PathMusic, "XDG_MUSIC_DIR", "Music", xdgUserDirs);
    GetDirectory(m_PathPictures, "XDG_PICTURES_DIR", "Pictures", xdgUserDirs);
    GetDirectory(m_PathVideos, "XDG_VIDEOS_DIR", "Videos", xdgUserDirs);
    GetDirectory(m_PathPublicShare, "XDG_PUBLICSHARE_DIR", "Public Share",
                 xdgUserDirs);
    GetDirectory(m_PathTemplates, "XDG_TEMPLATES_DIR", "Templates",
                 xdgUserDirs);
}

void LinuxAPI::Open(const std::filesystem::path file) {
    pid_t pid = fork();
    if (pid == 0) { // We are the new process

        // We must first detach from our parent process
        if (setsid() == -1) { // -1 indicates an error, so we close up shop
            std::cout
                << "Child: An error occured trying to split off from the main "
                   "process. Exiting."
                << std::endl;
            exit(1);
        }
        std::cout << "Child: Splitting up from parent process" << std::endl;

        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        // Open the file and exit with the appropriate status code
        exit(execlp("xdg-open", "xdg-open", file.c_str(), (char *)NULL));

    } else if (pid < 0) {
        ERROR("Failed to fork process!");
    }
}

std::string_view LinuxAPI::GetUserFolderPath(UserFolderType type) {
    switch (type) {
    case Home:
        return m_PathHome;
    case Desktop:
        return m_PathDesktop;
    case Documents:
        return m_PathDocuments;
    case Downloads:
        return m_PathDownloads;
    case Music:
        return m_PathMusic;
    case Pictures:
        return m_PathPictures;
    case Videos:
        return m_PathVideos;
    case Templates:
        return m_PathTemplates;
    case PublicShare:
        return m_PathPublicShare;
    default:
        return "";
    }
}

std::string_view LinuxAPI::GetHermesConfigFolder() { return m_PathConfig; }
} // namespace Hermes
#endif
