#include <QtWidgets>
#include "include/profsdlg.h"

ProfsDlg::ProfsDlg()
{
    createGridGroupBox();
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("filecryptor"));
}

void ProfsDlg::createGridGroupBox()
{
    QRadioButton *radio1 = new QRadioButton(tr("ECB mode"));
    QRadioButton *radio2 = new QRadioButton(tr("CBC mode"));
    QRadioButton *radio3 = new QRadioButton(tr("CFB mode"));
    QRadioButton *radio4 = new QRadioButton(tr("OFB mode"));
    QRadioButton *radio5 = new QRadioButton(tr("CTR mode"));

    gridGroupBox = new QGroupBox(tr("Encryption Profile"));
    QGridLayout *layout = new QGridLayout;

    layout->addWidget(radio1, 1, 0);
    layout->addWidget(radio2, 2, 0, Qt::AlignLeft);
    layout->addWidget(radio3, 3, 0, Qt::AlignLeft);
    layout->addWidget(radio4, 4, 0, Qt::AlignLeft);
    layout->addWidget(radio5, 5, 0, Qt::AlignLeft);

    radio1->setChecked(true);
    saveOriginal = new QCheckBox(tr("Preserve original file"));
    layout->addWidget(saveOriginal, 0, 1, 2, 1);

    layout->setColumnStretch(1, 10);
    layout->setColumnStretch(2, 20);
    gridGroupBox->setLayout(layout);
}
