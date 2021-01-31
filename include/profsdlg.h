#ifndef PROFSDLG_H_
#define PROFSDLG_H_

#include <QDialog>
#include <QFileSelector>
#include "profile.h"

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QPushButton;
class QLineEdit;
class QCheckBox;
class QPushButton;
class QRadioButton;
QT_END_NAMESPACE

class ProfsDlg : public QDialog
{
    Q_OBJECT

    QGroupBox *horizontalGroupBox;
    QGroupBox *gridGroupBox;
    QDialogButtonBox *buttonBox;

    QPushButton* dirSelect;
    QLineEdit* dirEdit;
    QRadioButton* radio1;

    QRadioButton* radio2;
    QRadioButton* radio3;
    QRadioButton* radio4;

    QRadioButton* radio5;
    QCheckBox* saveOriginal;
    QCheckBox* targetDir;

    QCheckBox* defProfile;
    void createHorizontalGroupBox(void);
    void createGridGroupBox(void);

    void populateGui(void);
    void populateStruct(void);
    encryptor::tPROFILE& _prof;

    void accept(void) override;

public:
    explicit ProfsDlg(encryptor::tPROFILE&, QWidget* parent = nullptr);

private slots:
    void enableTargetDir(bool);
    void selectDir(void);
};

#endif
