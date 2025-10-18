#include "File.h"

#include "Log.h"

namespace Hermes {
QVector<FileDescription>
ImmediateFileAPI::Files(const std::filesystem::path &path) {
    TRACE("Query: Files in {}", path.c_str());
    QVector<FileDescription> out;

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        auto filename = entry.path().filename().string();
        out.emplace_back(QString::fromStdString(filename.c_str()),
                         entry.is_directory(), filename[0] == '.');
    }

    TRACE("Query: Found {} file(s)", out.size());

    return out;
}
} // namespace Hermes
