#include "include/aboutdlg.h"
#include "ui_aboutdlg.h"

AboutDlg::AboutDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDlg)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    installEventFilter(this);
}

AboutDlg::~AboutDlg()
{
    delete ui;
}

bool AboutDlg::eventFilter(QObject* obj, QEvent* event)
{
    Q_UNUSED(obj)

    if (event->type() == QEvent::MouseButtonPress) {
        this->close();
        return true;
    }
    else
        return false;
}
