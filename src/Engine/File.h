#pragma once
#include <QObject>
#include <filesystem>

namespace Hermes {
struct FileDescription {
    QString Name;
    bool IsFolder;
    bool IsHidden;
};

class FileAPI {
  public:
    virtual ~FileAPI() = default;

    virtual QVector<FileDescription>
    Files(const std::filesystem::path &path) = 0;
};

class ImmediateFileAPI : public FileAPI {
  public:
    ImmediateFileAPI() {};
    ~ImmediateFileAPI() override {};

    QVector<FileDescription> Files(const std::filesystem::path &path) override;
};
} // namespace Hermes
