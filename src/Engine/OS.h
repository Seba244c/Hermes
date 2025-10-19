#pragma once

#include <filesystem>
#include <memory>
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

    virtual void Open(const std::filesystem::path file) = 0;

    virtual std::string_view GetName() = 0;
    virtual std::string_view GetVariant() = 0;
    virtual std::string_view GetVersion() = 0;

    virtual std::string_view GetUserFolderPath(UserFolderType type) = 0;
    virtual std::string_view GetHermesConfigFolder() = 0;
};

std::unique_ptr<OSApi> GetOSApi();

#ifdef HERMES_PLATFORM_LINUX
class LinuxAPI : public OSApi {
  public:
    LinuxAPI();

    void Open(const std::filesystem::path file) override;

    std::string_view GetName() override { return "Linux"; }
    std::string_view GetVariant() override;
    std::string_view GetVersion() override;

    std::string_view GetUserFolderPath(UserFolderType type) override;
    std::string_view GetHermesConfigFolder() override;

  private:
    void ParseUtsname();

  private:
    std::string m_PathHome, m_PathDesktop, m_PathDocuments, m_PathDownloads,
        m_PathMusic, m_PathPictures, m_PathVideos, m_PathTemplates,
        m_PathPublicShare, m_PathConfig;
    std::string m_Variant, m_Version;
};
#endif
} // namespace Hermes
