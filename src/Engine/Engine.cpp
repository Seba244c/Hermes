#include "Engine.h"

#include "Log.h"

namespace Hermes {
HermesEngine *HermesEngine::s_Instance;

void HermesEngine::PrintDiagnostics() {
    INFO("Running Hermes v. git");
    INFO("OS: Linux");
}

HermesEngine::HermesEngine() {
    assert(!s_Instance);
    s_Instance = this;

    // Log system configuration
    Hermes::Log::Init();
    PrintDiagnostics();

    // Initialize
    m_OS = std::make_unique<LinuxAPI>();

    // Set to start path
    OpenStartDir();
}

void HermesEngine::OpenStartDir() {
    switch (m_Settings.startingPathType) {
    case Settings::UserFolder:
        SetCurrentPath(
            m_OS->GetUserFolderPath(m_Settings.startingPathFolderType));
        break;
    case Settings::Path:
        if (SetCurrentPath(m_Settings.startingPathPath))
            return;

        WARN("Invalid starting path, opening home directory instead");
        SetCurrentPath(m_OS->GetUserFolderPath(Home));
        break;
    }
}

bool HermesEngine::SetCurrentPath(std::string_view path) {
    return SetCurrentPath(std::filesystem::path(path));
}
bool HermesEngine::SetCurrentPath(const QString &path) {
    return SetCurrentPath(std::filesystem::path(path.toStdString()));
}
bool HermesEngine::SetCurrentPath(std::filesystem::path path) {
    if (!std::filesystem::exists(path)) {
        WARN("Path does not exist: {}", path.string());
        WARN("Cannot set engine path to this path!");
        return false;
    }

    if (std::filesystem::exists(m_CurrentPath) && // By default, the path is ""
                                                  // which makes equivaent crash
        std::filesystem::equivalent(m_CurrentPath, path))
        return false;

    INFO("Changed engine path to {}", path.string());
    m_CurrentPath = path;
    return true;
}
} // namespace Hermes
