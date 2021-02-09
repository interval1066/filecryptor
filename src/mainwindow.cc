#include <include/mainwindow.h>
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
    _profdialog(std::make_unique<ProfsDlg>()),
    _pwdlg(std::make_unique<PWDialog>()),
    _about(std::make_unique<AboutDlg>())
{
    if((_profdialog->GetProfile()->_placement.x() > 10) &&
        (_profdialog->GetProfile()->_placement.y() > 10))
        resize(_profdialog->GetProfile()->_placement.x(),
               _profdialog->GetProfile()->_placement.y());
    else
        resize(_winx, _winy);

    initUI();
}

MainWindow::~MainWindow()
{
    _profdialog->GetProfile()->_placement.setX(geometry().width());
    _profdialog->GetProfile()->_placement.setY(geometry().height());
    _profdialog->SyncronizeSettings();
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
    connect(action1, &QAction::triggered, this, [this, &list](){ encryptSelected(list); });
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
MainWindow::encryptSelected(QList<QModelIndex>& list)
{
    _inputque.clear();
    _outputque.clear();

    if(_pwdlg->exec() == QDialog::Accepted) {
        for (int i = 0; i < list.size(); i++) {
            auto* item = itemModel->itemFromIndex(list.at(i));

            const QString& data = item->accessibleDescription();
            QFileInfo file(data);
            if(!file.isDir()) {

                _inputque.push_back(file.absoluteFilePath());
                _outputque.push_back(file.absoluteFilePath().append(".enc"));
            }
        }
        processFiles();
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
    auto* file = menuBar()->addMenu("&File");
    auto* open = new QAction(tr("&Open Profile"), this);
    open->setStatusTip(tr("Open existing profile"));

    file->addAction(open);
    auto* save = new QAction(tr("&Save Profile"), this);
    save->setStatusTip(tr("Save the current profile"));

    file->addAction(save);
    auto* saveAs = new QAction(tr("&Save Profile As..."), this);
    saveAs->setStatusTip(tr("Save the current profile with a new name"));

    file->addAction(saveAs);
    file->addSeparator();
    auto* quit = new QAction(tr("&Quit"), this);

    quit->setStatusTip(tr("Quit the application"));
    file->addAction(quit);
    auto* encrypt = menuBar()->addMenu(tr("&Encryption"));

    encryptItems = new QAction(tr("&Encrypt Selected"), this);
    encryptItems->setStatusTip(tr("Encrypt the selected items"));
    encrypt->addAction(encryptItems);

    encryptItems->setDisabled(true);
    decryptItems = new QAction(tr("&Decrypt Selected "), this);
    decryptItems->setStatusTip(tr("Decrypt the selected items"));

    encrypt->addAction(decryptItems);
    decryptItems->setDisabled(true);
    clearItems = new QAction(tr("&Clear Selected "), this);

    clearItems->setStatusTip(tr("Clear the selected items"));
    encrypt->addAction(clearItems);
    encrypt->addSeparator();

    auto* prefs = new QAction(tr("Encryption &Profile"), this);
    prefs->setStatusTip(tr("Displays the profile editor"));
    encrypt->addAction(prefs);

    auto* about = menuBar()->addMenu(tr("&About"));
    auto* appHelp = new QAction(tr("&Help"));
    appHelp->setStatusTip(tr("How to use filecryptor"));

    about->addAction(appHelp);
    about->addSeparator();
    auto* aboutApp = new QAction(tr("&About Encyrptor"), this);

    aboutApp->setStatusTip(tr("Copyright information, etc."));
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
    if(_about->exec() == QDialog::Accepted)
        _about->close();
}

void
MainWindow::profile()
{
    if(_profdialog->exec() == QDialog::Accepted) {}
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
    encryptSelected(list);
}

void
MainWindow::processFiles()
{
    auto local = new QThread;
    auto worker = new FileCopyer(local);

    worker->setSourcePaths(_inputque);
    worker->setDestinationPaths(_outputque);

    local->start();

}
