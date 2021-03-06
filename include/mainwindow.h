#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QStatusBar>
#include <QDir>
#include <QMenuBar>
#include <QMenu>
#include <QShortcut>
#include <QFileInfo>
#include <QFileDialog>
#include <QVector>
#include <memory>
#include <encryptitemmodel.h>
#include <pwdlg.h>
#include <aboutdlg.h>
#include <profsdlg.h>
#include <profile.h>
#include <filecopyer.h>
#include <crypto/rd128.h>
#include <consts.h>

/*enum tSERIALIZE_SETTINGS_TYPE
{
    GET_ENTER,
    SAVE_EXIT,
    GET_PROFILE,
    SAVE_PROFILE,
    SAVE_PROFILE_AS
};*/

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString _password;

    int _winx, _winy;
    QString _currentProfile;
    QVector<QString> _inputque;

    QVector<QString> _outputque;
    encryptor::tPROFILE _prof;
    QTreeView* treeView;

    EncryptItemModel* itemModel;
    QMenuBar* mainMenu;
    QMenu* file;
    QMenu* encrypt;

    QMenu* about;
    QStatusBar* statusBar;
    QAction* aboutAct;

    QAction* encryptItems;
    QAction* decryptItems;
    QAction* clearItems;

    std::unique_ptr<ProfsDlg> _profdialog;
    std::unique_ptr<PWDialog> _pwdlg;
    std::unique_ptr<AboutDlg> _about;

    void encryptSelected(QList<QModelIndex>&, QFile* dir = nullptr);
    void clearSelected(void);
    void decryptSelected(QList<QModelIndex>&);

    void setMainMenu(void);
    void aboutCryptor(void);
    bool eventFilter(QObject*, QEvent*) override;

    void encryptAfter(void);
    void profile(void);
    void processFiles(QString&, tENCRYPT_DECRYPT);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initUI();

    friend EncryptItemModel;

private slots:
    void onSelected(QModelIndex index);
    void onCustomContextMenu(const QPoint&);
};

#endif // MAINWINDOW_H
