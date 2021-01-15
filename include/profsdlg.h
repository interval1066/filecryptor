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
    void createHorizontalGroupBox();
    void createGridGroupBox();
    void populateProfile(void);
<<<<<<< HEAD

    void populateGui(void);
    std::shared_ptr<encryptor::tPROFILE> _prof;
=======
    std::shared_ptr<encryptor::Profile> _prof;
>>>>>>> 843f2f2ff9905305a5ba3eee0717404bb8ee1710

public:
    ProfsDlg(std::shared_ptr<encryptor::tPROFILE> const&, QWidget* parent = nullptr);

    inline std::shared_ptr<encryptor::tPROFILE> GetProfile()
    {
        return _prof;
    }

private slots:
    void enableTargetDir(bool);
    void selectDir(void);
};

#endif
