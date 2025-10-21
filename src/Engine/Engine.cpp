#include <cstdlib>

#include "Engine.h"

#include "Log.h"

namespace Hermes {
HermesEngine *HermesEngine::s_Instance;

void HermesEngine::PrintDiagnostics() {
    INFO("Running Hermes v. git");
    INFO("OS: {}", m_OS->GetName());
    INFO("OS Variant: {}", m_OS->GetVariant());
    INFO("OS Version: {}", m_OS->GetVersion());
}

HermesEngine::HermesEngine(QQuickItem *parent) : QQuickItem(parent) {
    assert(!s_Instance);
    s_Instance = this;

    // Log system configuration
    Hermes::Log::Init();
    m_OS = GetOSApi();
    PrintDiagnostics();

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
    currentPathChanged();
    canGoUpChanged();
    return true;
}

void HermesEngine::OpenFile(std::string_view path) {
    OpenFile(std::filesystem::path(path));
}
void HermesEngine::OpenFile(const QString &path) {
    OpenFile(std::filesystem::path(path.toStdString()));
}
void HermesEngine::OpenFile(std::filesystem::path path) {
    INFO("Opening file {}", path.string());
    m_OS->Open(path);
}
bool HermesEngine::CanGoUp() { return m_CurrentPath.has_parent_path(); }
bool HermesEngine::CanGoForward() { return false; }
bool HermesEngine::CanGoBack() { return false; }
void HermesEngine::GoUp() {
    auto parentPath = m_CurrentPath.parent_path();

    if (m_CurrentPath.string().ends_with("/")) // To handle trailing slashes
        parentPath = parentPath.parent_path();

    INFO("Going up to parent path: {}", parentPath.string());
    SetCurrentPath(parentPath);
}
void HermesEngine::GoForward() { WARN("Not implemented"); }
void HermesEngine::GoBack() { WARN("Not implemented"); }
} // namespace Hermes
