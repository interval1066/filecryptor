#ifndef ENCRYPTITEMMODEL_H_
#define ENCRYPTITEMMODEL_H_

#include <QStandardItemModel>
#include <QStandardItem>
#include <QFileSystemWatcher>

class EncryptItemModel : public QStandardItemModel
{
    QStandardItem* rootItem;
    QIcon dirIcon;
    QIcon fileIcon;
    QIcon encryptedIcon;
    QIcon videoIcon;
    QFileSystemWatcher watcher;

public:
    EncryptItemModel(QObject* parent = nullptr);
    ~EncryptItemModel();

    void setModelDetails(QString names);
    void populateModel(const QStringList &names);
    void createDirectoryItem(QString dirName, QStandardItem *parentItem = NULL);
};

#endif
