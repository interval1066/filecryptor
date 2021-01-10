#include <QtWidgets>

#include "include/pwdlg.h"

PWDialog::PWDialog()
{
    createFormGroupBox();
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    QVBoxLayout *mainLayout = new QVBoxLayout;

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
    formGroupBox = new QGroupBox();
    QFormLayout *layout = new QFormLayout;

    layout->addRow(new QLabel(tr("Enter password:")), new QLineEdit);
    layout->addRow(new QLabel(tr("Confirm password:")), new QLineEdit);

    formGroupBox->setLayout(layout);
}

