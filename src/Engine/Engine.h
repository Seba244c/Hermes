#pragma once
#include <QString>
#include <cassert>
#include <cstdint>
#include <filesystem>
#include <memory>

#include "Engine/OS.h"

namespace Hermes {
struct Settings {
    enum StartingPathType : uint8_t {
        UserFolder,
        Path,
    };

    StartingPathType startingPathType = UserFolder;
    QString startingPathPath;
    UserFolderType startingPathFolderType = Home;
};

class HermesEngine {
  public:
    HermesEngine();
    static HermesEngine *Instance() {
        assert(s_Instance);
        return s_Instance;
    }

    bool SetCurrentPath(std::string_view path);
    bool SetCurrentPath(std::filesystem::path path);
    bool SetCurrentPath(const QString &path);
    std::filesystem::path GetCurrentPath() { return m_CurrentPath; }

  private:
    void PrintDiagnostics();
    void OpenStartDir();

  private:
    std::unique_ptr<OSApi> m_OS;
    std::filesystem::path m_CurrentPath;
    Settings m_Settings;
    static HermesEngine *s_Instance;
};
} // namespace Hermes
