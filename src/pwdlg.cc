#include <QtWidgets>

#include <pwdlg.h>
#include <crypto/rd128.h>

PWDialog::PWDialog(QWidget* parent)
    : QDialog(parent)
{
    createFormGroupBox();
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
        | QDialogButtonBox::Cancel, this);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Enter encryption password"));
    resize(400, 130);
    setFixedSize(size());

    setModal(true);
}

void
PWDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(this);
    QFormLayout *layout = new QFormLayout(this);

    lineEdit1 = new QLineEdit(this);
    lineEdit2 = new QLineEdit(this);

    layout->addRow(new QLabel(tr("Enter password:")), lineEdit1);
    layout->addRow(new QLabel(tr("Confirm password:")), lineEdit2);

    formGroupBox->setLayout(layout);
}

void
PWDialog::accept()
{
    const QString pw1 = lineEdit1->text();
    const QString pw2 = lineEdit2->text();

    if(QString::compare(pw1, pw2, Qt::CaseSensitive) == 0) {
        char* p = pw1.toLocal8Bit().data();
        crypto::RD128 rd128(p, strlen(p));

        _pw = rd128.hexdigest();
    }
    else {
        _pw.clear();
        if(_pw.isEmpty()) {
            qDebug("Empty");
            QMessageBox msgBox;
            msgBox.setText(tr("Password verification failed."));
            msgBox.exec();
        }
    }
    lineEdit1->clear();
    lineEdit2->clear();
    QDialog::accept();
}

void
PWDialog::reject()
{
    QDialog::reject();
}

const QString
PWDialog::GetPW()
{
    return _pw;
}
