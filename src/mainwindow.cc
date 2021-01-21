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
      _winx(700), _winy(500),
      _profile(std::make_shared<encryptor::tPROFILE>()),
      _pwdlg(std::make_unique<PWDialog>()),
    _about(std::make_unique<AboutDlg>())
{
    auto appname = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
    auto settings = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QSettings _settings(settings + "/" + appname + ".ini", QSettings::IniFormat);

    if(!QDir(settings).exists())
        resize(_winx, _winy);
    else {

        QSettings _settings(settings + "/" + appname + ".ini", QSettings::IniFormat);
        _settings.beginGroup("MAINUI");

        _winx = _settings.value("winx").toInt();
        _winy = _settings.value("winy").toInt();

        _settings.endGroup();
        _settings.beginGroup("ENCRYPTOPTION");
        int mode = _settings.value("mode").toInt();

        switch(mode) {
            case encryptor::MODE_ECB:
                _profile->mode = encryptor::MODE_ECB;
                break;

            case encryptor::MODE_CBC:
                _profile->mode = encryptor::MODE_CBC;
                break;

            case encryptor::MODE_CFB:
                _profile->mode = encryptor::MODE_CFB;
                break;

            case encryptor::MODE_OFB:
                _profile->mode = encryptor::MODE_OFB;
                break;

            case encryptor::MODE_CTR:
                _profile->mode = encryptor::MODE_CTR;
                break;
        }

        _profile->preserveFile = _settings.value("preserveFile").toInt();
        _profile->makeDefault = _settings.value("makeDefault").toInt();
        _profile->setTargetDir = _settings.value("setTargetDir").toInt();

        _profile->targetDir = _settings.value("targetDir").toString();
        _profile->defProfile = _settings.value("defaultProf").toString();
        _profile->lastDir = _settings.value("lastDir").toString();

        _settings.endGroup();
        resize(_winx, _winy);
    }
    _profdialog = std::make_unique<ProfsDlg>(_profile, this);

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
    _settings.beginGroup("ENCRYPTOPTION");
    _settings.setValue("mode", _profile->mode);

    _settings.setValue("preserveFile", _profile->preserveFile);
    _settings.setValue("makeDefault", _profile->makeDefault);
    _settings.setValue("setTargetDir", _profile->setTargetDir);

    _settings.setValue("targetDir", _profile->targetDir);
    _settings.setValue("defaultProf", _profile->defProfile);
    _settings.setValue("lastDir", _profile->lastDir);

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
    treeView = new QTreeView(this);
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

    auto* action = contextMenu->addAction(tr("Decrypt Selected"));
    auto* action1 = contextMenu->addAction(tr("Encrypt Selected"));
    auto* action2 = contextMenu->addAction(tr("Clear Selected"));

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

    auto index = treeView->indexAt(point);
    if (index.isValid())
        contextMenu->exec(treeView->viewport()->mapToGlobal(point));
}

void
MainWindow::testfunc1(QList<QModelIndex>& list)
{
    if(_pwdlg->exec() == QDialog::Accepted) {
        for (int i = 0; i < list.size(); i++) {
            auto* item = itemModel->itemFromIndex(list.at(i));

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
            auto* item = itemModel->itemFromIndex(list.at(i));

            const QString& data = item->accessibleDescription();
            qDebug("%s", qPrintable(data));
        }
    }
}

void
MainWindow::setMainMenu()
{
    //tFILEIO_TYPE type;
    auto* file = menuBar()->addMenu("&File");
    auto* open = new QAction("&Open Profile", this);
    file->addAction(open);

    auto* save = new QAction("&Save Profile", this);
    file->addAction(save);
    save->setDisabled(true);

    auto* saveAs = new QAction("&Save Profile As...", this);
    file->addAction(saveAs);
    file->addSeparator();

    auto* quit = new QAction("&Quit", this);
    file->addAction(quit);

    auto* encrypt = menuBar()->addMenu("&Encryption");
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

    auto* about = menuBar()->addMenu("&About");
    auto* appHelp = new QAction("&Help");
    about->addAction(appHelp);

    auto* aboutApp = new QAction("&About Encyrptor", this);
    about->addAction(aboutApp);

    connect(open, &QAction::triggered, this, [&]() { tFILEIO_TYPE type = OPEN; MainWindow::fileIO(type); });
    connect(save, &QAction::triggered, this, [&]() { tFILEIO_TYPE type = SAVE; MainWindow::fileIO(type); });
    connect(saveAs, &QAction::triggered, this, [&]() { tFILEIO_TYPE type = SAVEAS; MainWindow::fileIO(type); });

    connect(quit, &QAction::triggered, qApp, QApplication::quit);
    connect(encryptItems, &QAction::triggered, this, &MainWindow::encryptAfter);
    connect(clearItems, &QAction::triggered, this, &MainWindow::clearSelected);

    connect(prefs, &QAction::triggered, this, &MainWindow::profile);
    connect(aboutApp, &QAction::triggered, this, &MainWindow::aboutCryptor);
 }

void
MainWindow::aboutCryptor()
{
    if(_about->exec() == QDialog::Accepted)
        _about->close();
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
    if(_profdialog->exec() == QDialog::Accepted) { }
    _profile = _profdialog->getProfile();
}

void
MainWindow::fileIO(tFILEIO_TYPE& type)
{
    QString startDir, openFile;
    if(_profile->lastDir.size() < 1)
        startDir = QDir::homePath();
    else
        startDir = _profile->lastDir;

    switch(type) {
    case OPEN:
        openFile = QFileDialog::getOpenFileName(this, tr("Open encryption profile"),
            startDir, tr("Profile (*.ini);;All Files (*)"));
        break;

    case SAVE:
        openFile = QFileDialog::getSaveFileName(this, tr("Save encryption profile"),
            startDir, tr("Profile (*.ini);;All Files (*)"));
         break;

    case SAVEAS:
        openFile = QFileDialog::getSaveFileName(this, tr("Save encryption profile As"),
            startDir, tr("Profile (*.ini);;All Files (*)"));
        break;
    }

    if(!openFile.isNull())
        _profile->lastDir = QFileInfo(openFile).path();
}
