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
#include <memory>
#include "encryptitemmodel.h"
#include "pwdlg.h"
#include "aboutdlg.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    PWDialog* _pwdlg;
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

    int _winx, _winy;

    void testfunc1(QList<QModelIndex>&);
    void clearSelected(void);
    void decryptSelected(QList<QModelIndex>&);

    void setMainMenu(void);
    void aboutCryptor(void);
    bool eventFilter(QObject*, QEvent*) override;

    void encryptAfter(void);

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initUI();

    friend EncryptItemModel;

private slots:
    void onSelected(QModelIndex index);
    void onCustomContextMenu(const QPoint&);
};

#endif // MAINWINDOW_H
