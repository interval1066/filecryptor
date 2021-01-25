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
#include <memory>
#include "encryptitemmodel.h"
#include "pwdlg.h"
#include "aboutdlg.h"
#include "profsdlg.h"
#include "profile.h"

enum tFILEIO_TYPE
{
    OPEN, SAVE, SAVEAS
};

enum tSERIALIZE_SETTINGS_TYPE
{
    GET_ENTER,
    SAVE_EXIT,
    GET_PROFILE,
    SAVE_PROFILE,
    SAVE_PROFILE_AS
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    int _winx, _winy;
    bool _bnoProfile;
    QString _currentProfile;
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

    std::shared_ptr<encryptor::tPROFILE> _profile;
    std::unique_ptr<ProfsDlg> _profdialog;
    std::unique_ptr<PWDialog> _pwdlg;

    std::unique_ptr<AboutDlg> _about;

    void encryptSelected(QList<QModelIndex>&);
    void clearSelected(void);
    void decryptSelected(QList<QModelIndex>&);

    void setMainMenu(void);
    void aboutCryptor(void);
    bool eventFilter(QObject*, QEvent*) override;

    void encryptAfter(void);
    void profile(void);
    void fileIO(tFILEIO_TYPE&);

    void serializeSettings(tSERIALIZE_SETTINGS_TYPE);

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
