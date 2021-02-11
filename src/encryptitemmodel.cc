#include <encryptitemmodel.h>

#include <QApplication>
#include <QStyle>
#include <QDir>
#include <QDebug>
#include <QDirIterator>
#include <QTreeView>
#include <QMimeDatabase>
//#include <QDebug>

EncryptItemModel::EncryptItemModel(QObject *parent)
    :QStandardItemModel(parent)
{
    rootItem = this->invisibleRootItem();
    dirIcon = QApplication::style()->standardIcon(QStyle::SP_DirIcon);      //icon for directories
    fileIcon = QApplication::style()->standardIcon(QStyle::SP_FileIcon);    //icon for files
    videoIcon = QApplication::style()->standardIcon(QStyle::SP_MediaVolume);
    encryptedIcon = QIcon(":/res/data-encryption.png");
    //videoIcon = QIcon(":/res/png-video.png");
    QTreeView view;
}

EncryptItemModel::~EncryptItemModel()
{

}

void
EncryptItemModel::setModelDetails(QString names)
{
    populateModel(names.split("\n"));
}

void
EncryptItemModel::populateModel(const QStringList &names)
{
    QString name;
    QStandardItem* parent;

    foreach (name, names) {
        if(!name.isEmpty()) {
            name.remove("\r");

            parent = new QStandardItem(dirIcon, name); //create the parent directory item
            parent->setAccessibleDescription(name);     //set actual path to item
            rootItem->appendRow(parent);                //add the parent item to root item

            createDirectoryItem(name, parent);          //Iterate and populate the contents
        }
    }
}

void
EncryptItemModel::createDirectoryItem(QString dirName, QStandardItem *parentItem)
{
    QDir dir(dirName);
    QFileInfoList subFolders;
    QFileInfo folderName;

    QStandardItem* child;
    subFolders = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);    //get all the sub folders
    QMimeDatabase db;

    QBrush encryptedBrush, plainBrush;
    encryptedBrush.setColor(QColor(0, 150, 0));
    plainBrush.setColor(QColor(170, 0, 0));

    foreach(folderName, subFolders) {
        if(folderName.isFile()) {
            child = new QStandardItem(videoIcon, folderName.fileName());                 //Append a file

            child->setForeground(plainBrush);
            child->setAccessibleDescription(folderName.filePath());                     //set actual path to item
            //QMimeType type = db.mimeTypeForFile(folderName.filePath());
            //QString blah = type.name();
            //qDebug("%s", qUtf8Printable(blah));
        }
        else {
            child = new QStandardItem(dirIcon, folderName.fileName());                  //Append a folder
            child->setAccessibleDescription(folderName.filePath());                     //set actual path to item
        }
        parentItem->appendRow(child);
        createDirectoryItem(folderName.filePath(), child);                              //Recurse its subdirectories
    }
}
