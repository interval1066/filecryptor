#include <QtWidgets>
#include "include/profsdlg.h"

ProfsDlg::ProfsDlg(encryptor::tPROFILE& prof, QWidget* parent) :
   QDialog(parent), _prof(prof)
{
    createGridGroupBox();
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);

    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(gridGroupBox);

    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    resize(480, 140);

    setWindowTitle(tr("filecryptor"));
    populateGui();
}

void
ProfsDlg::createGridGroupBox()
{
    auto* layout = new QGridLayout(this);
    radio1 = new QRadioButton(tr("ECB mode"), this);
    radio2 = new QRadioButton(tr("CBC mode"), this);

    radio3 = new QRadioButton(tr("CFB mode"), this);
    radio4 = new QRadioButton(tr("OFB mode"), this);
    radio5 = new QRadioButton(tr("CTR mode"), this);

    gridGroupBox = new QGroupBox(tr("Encryption Profile"), this);
    layout->addWidget(radio1, 1, 0);
    layout->addWidget(radio2, 2, 0, Qt::AlignLeft);

    layout->addWidget(radio3, 3, 0, Qt::AlignLeft);
    layout->addWidget(radio4, 4, 0, Qt::AlignLeft);
    layout->addWidget(radio5, 5, 0, Qt::AlignLeft);

    radio1->setChecked(true);
    saveOriginal = new QCheckBox(tr("Preserve original file"), this);
    layout->addWidget(saveOriginal, 1, 2, 1, 1);

    defProfile = new QCheckBox(tr("Save as default profile"));
    layout->addWidget(defProfile, 2, 2, 1, 2);
    targetDir = new QCheckBox(tr("Place encrypted files in this directory"), this);

    layout->addWidget(targetDir, 3, 2, 1, 2);
    dirSelect = new QPushButton(tr("Select Directory"), this);

    layout->addWidget(dirSelect, 4, 2, 1, 1);
    dirSelect->setEnabled(false);
    dirEdit = new QLineEdit(this);

    layout->addWidget(dirEdit, 5, 2, 1, 1);
    dirEdit->setEnabled(false);
    gridGroupBox->setLayout(layout);

    connect(targetDir, &QCheckBox::clicked, this, &ProfsDlg::enableTargetDir);
    connect(dirSelect, &QPushButton::clicked, this, &ProfsDlg::selectDir);
}

void
ProfsDlg::enableTargetDir(bool bEnable)
{
    dirSelect->setEnabled(bEnable);
    dirEdit->setEnabled(bEnable);
}

void
ProfsDlg::populateGui()
{
    encryptor::tAESMODES mode = _prof._mode;
    switch(mode) {
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

    (_prof._preserveFile == 1)? saveOriginal->setChecked(true) :
        saveOriginal->setChecked(false);

    (_prof._makeDefault == 1)? defProfile->setChecked(true) :
        defProfile->setChecked(false);

    bool enabled = false;
    (_prof._setTargetDir == 1)? enabled = true :
        enabled = false;

    dirSelect->setEnabled(enabled);
    targetDir->setChecked(enabled);
    dirEdit->setEnabled(enabled);

    dirEdit->setText(_prof._targetDir);
}

void
ProfsDlg::populateStruct()
{
    if(radio1->isChecked())
        _prof._mode = encryptor::MODE_ECB;
    else if(radio2->isChecked())
        _prof._mode = encryptor::MODE_CBC;
    else if(radio3->isChecked())
        _prof._mode = encryptor::MODE_CFB;
    else if(radio4->isChecked())
        _prof._mode = encryptor::MODE_OFB;
    else if(radio5->isChecked())
        _prof._mode = encryptor::MODE_CTR;

    saveOriginal->isChecked()? _prof._preserveFile = 1 :
        _prof._preserveFile = 0;

    defProfile->isChecked()? _prof._makeDefault = 1 :
        _prof._makeDefault = 0;

    targetDir->isChecked()? _prof._setTargetDir = 1:
        _prof._setTargetDir = 0;

    _prof._targetDir = dirEdit->text();

}

void
ProfsDlg::selectDir()
{
    if(_prof._lastDir.size() < 1)
        QDir::currentPath();

    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Directory"),
        _prof._lastDir, QFileDialog::ShowDirsOnly
        | QFileDialog::DontResolveSymlinks);

     dirEdit->setText(dir);
     _prof._lastDir = dir;
}

void ProfsDlg::accept()
{
    populateStruct();
    QDialog::accept();
}
