#include "include/mainwindow.h"

#include <QHeaderView>
#include <QFile>
#include <QStandardPaths>
#include <iostream>
#include <QStandardPaths>
#include <QSettings>
#include <QCoreApplication>
#include <QObject>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _profdialog(std::make_unique<ProfsDlg>()),
      _pwdlg(std::make_unique<PWDialog>()),
      _winx(600), _winy(480)
{
    auto appname = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
    auto settings = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    if(!QDir(settings).exists())
        QDir().mkdir(settings);

    QSettings _settings(settings + "/" + appname + ".ini", QSettings::IniFormat);
    _settings.beginGroup("MAINUI");

    _winx = _settings.value("winx").toInt();
    _winy = _settings.value("winy").toInt();

    _settings.endGroup();
    resize(_winx, _winy);

    initUI();
}

MainWindow::~MainWindow()
{
    auto appname = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
    auto settings = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    int hsize = size().height();
    int wsize = size().width();

    QSettings _settings(settings + "/" + appname + ".ini", QSettings::IniFormat);
    _settings.beginGroup("MAINUI");

    _settings.setValue("winx", QString::number(wsize));
    _settings.setValue("winy", QString::number(hsize));

    _settings.endGroup();
    _settings.sync();
}

void
MainWindow::initUI()
{
    setMainMenu();
    statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);
    itemModel = new EncryptItemModel();

    itemModel->setModelDetails(QDir::homePath());
    treeView = new QTreeView();
    treeView->setModel(itemModel);

    treeView->setSelectionMode(QTreeView::MultiSelection);
    setCentralWidget(treeView);
    treeView->expand(itemModel->index(0, 0, QModelIndex()));

    treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    treeView->setMouseTracking(true);
    treeView->viewport()->installEventFilter(this);

    connect(treeView, &QTreeView::clicked, this, &MainWindow::onSelected);
    connect(treeView, &QWidget::customContextMenuRequested, this,
        &MainWindow::onCustomContextMenu);
}

void
MainWindow::onSelected(QModelIndex index)
{
    statusBar->showMessage(const_cast<QStandardItem*>
        (itemModel->itemFromIndex(index))->accessibleDescription());

    auto list = treeView->selectionModel()->selectedIndexes();
    if(list.size() < 1) {

        encryptItems->setDisabled(true);
        decryptItems->setDisabled(true);
        clearItems->setDisabled(true);
    }
    else {
        encryptItems->setDisabled(false);
        decryptItems->setDisabled(false);
        clearItems->setDisabled(false);
    }
}

void
MainWindow::onCustomContextMenu(const QPoint& point)
{
    auto contextMenu = std::make_unique<QMenu>();
    auto list = treeView->selectionModel()->selectedIndexes();

    QAction *action = contextMenu->addAction(tr("Decrypt Selected"));
    QAction *action1 = contextMenu->addAction(tr("Encrypt Selected"));
    QAction *action2 = contextMenu->addAction(tr("Clear Selected"));

    connect(action, &QAction::triggered, this, [this, &list](){ decryptSelected(list); });
    connect(action1, &QAction::triggered, this, [this, &list](){ testfunc1(list); });
    connect(action2, &QAction::triggered, this, &MainWindow::clearSelected);

    if(list.size() < 1) {
        action->setDisabled(true);
        action1->setDisabled(true);
        encryptItems->setDisabled(true);
        decryptItems->setDisabled(true);
        clearItems->setDisabled(true);
    }

    QModelIndex index = treeView->indexAt(point);
    if (index.isValid())
        contextMenu->exec(treeView->viewport()->mapToGlobal(point));
}

void
MainWindow::testfunc1(QList<QModelIndex>& list)
{
    if(_pwdlg->exec() == QDialog::Accepted) {
        for (int i = 0; i < list.size(); i++) {
            QStandardItem* item = itemModel->itemFromIndex(list.at(i));

            const QString& data = item->accessibleDescription();
            QFileInfo file(data);
            if(!file.isDir()) {

                qDebug("%s %s", qPrintable(file.completeBaseName() + ".enc"), qPrintable(file.absolutePath()));

            }
        }
    }
}

void
MainWindow::clearSelected()
{
    treeView->selectionModel()->clearSelection();
    encryptItems->setDisabled(true);
    decryptItems->setDisabled(true);
    clearItems->setDisabled(true);
}

void
MainWindow::decryptSelected(QList<QModelIndex>& list)
{
    if(_pwdlg->exec() == QDialog::Accepted) {
        for (int i = 0; i < list.size(); i++) {
            QStandardItem* item = itemModel->itemFromIndex(list.at(i));

            const QString& data = item->accessibleDescription();
            qDebug("%s", qPrintable(data));
        }
    }
}

void
MainWindow::setMainMenu()
{
    QMenu* file = menuBar()->addMenu("&File");
    auto* open = new QAction("&Open Profile", this);
    file->addAction(open);

    auto* save = new QAction("&Save Profile ", this);
    file->addAction(save);
    file->addSeparator();

    auto* quit = new QAction("&Quit", this);
    file->addAction(quit);

    QMenu* encrypt = menuBar()->addMenu("&Encryption");
    encryptItems = new QAction("&Encrypt Selected", this);
    encrypt->addAction(encryptItems);

    encryptItems->setDisabled(true);
    decryptItems = new QAction("&Decrypt Selected ", this);
    encrypt->addAction(decryptItems);

    decryptItems->setDisabled(true);
    clearItems = new QAction("&Clear Selected ", this);
    encrypt->addAction(clearItems);

    encrypt->addSeparator();
    auto* prefs = new QAction("Encryption &Profile", this);

    encrypt->addAction(prefs);
    QMenu* about = menuBar()->addMenu("&About");
    auto* aboutApp = new QAction("&About Encyrptor", this);

    about->addAction(aboutApp);
    connect(quit, &QAction::triggered, qApp, QApplication::quit);
    connect(encryptItems, &QAction::triggered, this, &MainWindow::encryptAfter);
    connect(clearItems, &QAction::triggered, this, &MainWindow::clearSelected);
    connect(prefs, &QAction::triggered, this, &MainWindow::profile);
    connect(aboutApp, &QAction::triggered, this, &MainWindow::aboutCryptor);
 }

void
MainWindow::aboutCryptor()
{
    AboutDlg* about = new AboutDlg;
    about->setAttribute(Qt::WA_DeleteOnClose);

    if(about->exec() == QDialog::Accepted)
        about->close();
}

bool
MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    auto list = treeView->selectionModel()->selectedIndexes();
    if (event->type() == QEvent::MouseMove) {
        if(list.size() < 1) {

            encryptItems->setDisabled(true);
            decryptItems->setDisabled(true);
            clearItems->setDisabled(true);
        }
        else {
            encryptItems->setDisabled(false);
            decryptItems->setDisabled(false);
            clearItems->setDisabled(false);
        }
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void
MainWindow::encryptAfter()
{
    auto list = treeView->selectionModel()->selectedIndexes();
    testfunc1(list);
}

void
MainWindow::profile()
{
    _profdialog->exec();
}
