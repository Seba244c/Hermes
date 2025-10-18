#include "FileList.h"

#include "Log.h"

namespace Hermes {
FileListModel::FileListModel(QObject *parent) : QAbstractListModel(parent) {
    SetCurrentPath("/home/ssnoer/Dev");
}

// Required QAbstractListModel overrides
int FileListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return m_Files.size();
}

QVariant FileListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_Files.size())
        return QVariant();

    const auto &file = m_Files[index.row()];

    switch (role) {
    case NameRole:
        return file.Name;
    case IsFolderRole:
        return file.IsFolder;
    default:
        return QVariant();
    }

    return {};
}
QHash<int, QByteArray> FileListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IsFolderRole] = "isFolder";
    return roles;
}

void FileListModel::Refresh() { LoadDirectory(m_CurrentPath); }

void FileListModel::SetCurrentPath(const QString &path) {
    TRACE("Changed path to {}", path.toStdString());
    if (m_CurrentPath == path)
        return;

    m_CurrentPath = path;
    emit currentPathChanged();
    LoadDirectory(path);
}

void FileListModel::LoadDirectory(const QString &path) {
    beginResetModel();

    INFO("Openening Directory {}", path.toStdString());
    std::filesystem::path currentDir(path.toStdString());
    Hermes::ImmediateFileAPI api;
    m_Files = api.Files(currentDir);

    endResetModel();
}
} // namespace Hermes
