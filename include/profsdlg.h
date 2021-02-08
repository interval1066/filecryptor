#ifndef PROFSDLG_H_
#define PROFSDLG_H_

#include <QtWidgets>
#include <QDialog>
#include <QFileSelector>
#include <include/settings.h>
#include <include/profile.h>

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
    encryptor::tPROFILE _prof, _profbak;
    void createHorizontalGroupBox(void);

    void createGridGroupBox(void);
    void populateGui(void);
    void populateStruct(void);

    void accept(void) override;
    void reject(void) override;
    void thisShowEvent(void);

protected:
    void showEvent(QShowEvent*) override;

public:
    explicit ProfsDlg(QWidget* parent = nullptr);
    encryptor::tPROFILE* GetProfile(void) { return &_prof; }
    void SyncronizeSettings(void) { iSettings::putSettings(_prof); }

private slots:
    void enableTargetDir(bool);
    void selectDir(void);
};

#endif
