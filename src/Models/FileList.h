#pragma once
#include <QAbstractListModel>
#include <QObject>

#include "Engine/File.h"

namespace Hermes {
class FileListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QString currentPath READ CurrentPath NOTIFY currentPathChanged)

  public:
    enum FileRoles {
        NameRole = Qt::UserRole + 1,
        IsFolderRole,
    };

    explicit FileListModel(QObject *parent = nullptr);

    Q_INVOKABLE void Refresh();
    Q_INVOKABLE void Open(const QString &path);

    // Required QAbstractListModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Variables
    QString CurrentPath() const { return m_CurrentPath; }
    void SetCurrentPath(const QString &path);

  signals:
    void currentPathChanged();

  private:
    void LoadDirectory(const QString &path);

    QVector<FileDescription> m_Files;
    QString m_CurrentPath;
};
} // namespace Hermes
