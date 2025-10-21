#include <filesystem>

#include "FileList.h"

#include "Engine/Engine.h"
#include "Log.h"

namespace Hermes {
FileListModel::FileListModel(QObject *parent) : QAbstractListModel(parent) {
    SetCurrentPath(HermesEngine::Instance()->GetCurrentPath().c_str());
    connect(
        HermesEngine::Instance(), &HermesEngine::currentPathChanged, [this]() {
            this->SetCurrentPath(
                QString(HermesEngine::Instance()->GetCurrentPath().c_str()));
        });
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
    m_CurrentPath = path;
    if (!m_CurrentPath.endsWith('/'))
        m_CurrentPath = m_CurrentPath + "/";

    emit currentPathChanged();
    LoadDirectory(path);
}

void FileListModel::LoadDirectory(const QString &path) {
    beginResetModel();

    TRACE("Loading Directory {}", path.toStdString());
    std::filesystem::path currentDir(path.toStdString());
    Hermes::ImmediateFileAPI api;
    m_Files = api.Files(currentDir);

    endResetModel();
}

void FileListModel::Open(const QString &path) {
    if (path.endsWith("/"))
        HermesEngine::Instance()->SetCurrentPath(m_CurrentPath + path);
    else
        HermesEngine::Instance()->OpenFile(m_CurrentPath + path);
}
} // namespace Hermes
