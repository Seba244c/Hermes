#pragma once

#include <string>
namespace Hermes {
enum UserFolderType {
    Home,
    Desktop,
    Documents,
    Downloads,
    Music,
    Pictures,
    Videos,
    Templates,
    PublicShare,
};

class OSApi {
  public:
    virtual ~OSApi() = default;

    virtual std::string_view GetUserFolderPath(UserFolderType type) = 0;
    virtual std::string_view GetHermesConfigFolder() = 0;
};

class LinuxAPI : public OSApi {
  public:
    LinuxAPI();

    std::string_view GetUserFolderPath(UserFolderType type) override;
    std::string_view GetHermesConfigFolder() override;

  private:
    std::string m_PathHome, m_PathDesktop, m_PathDocuments, m_PathDownloads,
        m_PathMusic, m_PathPictures, m_PathVideos, m_PathTemplates,
        m_PathPublicShare, m_PathConfig;
};
} // namespace Hermes
