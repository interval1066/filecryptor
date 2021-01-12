#include <QtWidgets>
#include "include/profsdlg.h"

ProfsDlg::ProfsDlg(std::shared_ptr<encryptor::Profile>& prof, QWidget* parent) :
   QDialog(parent), _prof(prof)
{
    createGridGroupBox();
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    resize(480, 140);
    setWindowTitle(tr("filecryptor"));
}

void
ProfsDlg::createGridGroupBox()
{
    radio1 = new QRadioButton(tr("ECB mode"), this);
    radio2 = new QRadioButton(tr("CBC mode"), this);
    radio3 = new QRadioButton(tr("CFB mode"), this);

    radio4 = new QRadioButton(tr("OFB mode"), this);
    radio5 = new QRadioButton(tr("CTR mode"), this);
    gridGroupBox = new QGroupBox(tr("Encryption Profile"), this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(radio1, 1, 0);
    layout->addWidget(radio2, 2, 0, Qt::AlignLeft);

    layout->addWidget(radio3, 3, 0, Qt::AlignLeft);
    layout->addWidget(radio4, 4, 0, Qt::AlignLeft);
    layout->addWidget(radio5, 5, 0, Qt::AlignLeft);

    radio1->setChecked(true);
    QCheckBox* saveOriginal = new QCheckBox(tr("Preserve original file"), this);
    layout->addWidget(saveOriginal, 1, 2, 1, 1);

    QCheckBox* targetDir = new QCheckBox(tr("Place encrypted files in this directory"), this);
    layout->addWidget(targetDir, 2, 2, 1, 2);
    targetDir->setChecked(false);

    dirSelect = new QPushButton(tr("Select Directory"), this);
    layout->addWidget(dirSelect, 3, 2, 1, 1);
    dirSelect->setEnabled(false);

    dirEdit = new QLineEdit(this);
    layout->addWidget(dirEdit, 4, 2, 1, 1);
    dirEdit->setEnabled(false);

    gridGroupBox->setLayout(layout);
    connect(targetDir, &QCheckBox::clicked, this, &ProfsDlg::enableTargetDir);
}

void
ProfsDlg::enableTargetDir(bool bEnable)
{
    dirSelect->setEnabled(bEnable);
    dirEdit->setEnabled(bEnable);
}

void
ProfsDlg::populateProfile()
{
}

void
ProfsDlg::populateGui()
{
    switch(_prof->mode) {
    case encryptor::MODE_ECB:
        radio1->setChecked(true);
        break;

    case encryptor::MODE_CBC:
        radio2->setChecked(true);
        break;

    case encryptor::MODE_CFB:
        radio3->setChecked(true);
        break;

    case encryptor::MODE_OFB:
        radio4->setChecked(true);
        break;

    case encryptor::MODE_CTR:
        radio5->setChecked(true);
        break;

    default:
        radio1->setChecked(true);
        break;
    }

    (saveOriginal->checkState())? _prof->preserveFile = 1 :
        _prof->preserveFile = 0;
}
