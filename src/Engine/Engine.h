#pragma once
#include <QQuickItem>
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

class HermesEngine : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(bool canGoUp READ CanGoUp NOTIFY canGoUpChanged)
    Q_PROPERTY(bool canGoBack READ CanGoBack NOTIFY canGoBackChanged)
    Q_PROPERTY(bool canGoForward READ CanGoForward NOTIFY canGoForwardChanged)
    Q_PROPERTY(std::filesystem::path currentPath READ GetCurrentPath NOTIFY
                   currentPathChanged)
  public:
    explicit HermesEngine(QQuickItem *iParent = 0);

    static HermesEngine *Instance() {
        assert(s_Instance);
        return s_Instance;
    }

    Q_INVOKABLE bool SetCurrentPath(const QString &path);
    bool SetCurrentPath(std::string_view path);
    bool SetCurrentPath(std::filesystem::path path);
    std::filesystem::path GetCurrentPath() { return m_CurrentPath; }

    void OpenFile(std::string_view path);
    void OpenFile(std::filesystem::path path);
    void OpenFile(const QString &path);

    bool CanGoUp();
    bool CanGoForward();
    bool CanGoBack();
    Q_INVOKABLE void GoUp();
    Q_INVOKABLE void GoForward();
    Q_INVOKABLE void GoBack();

  signals:
    void canGoUpChanged();
    void canGoBackChanged();
    void canGoForwardChanged();
    void currentPathChanged();

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
