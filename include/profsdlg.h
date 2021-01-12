#ifndef PROFSDLG_H_
#define PROFSDLG_H_

#include <QDialog>
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
QT_END_NAMESPACE

class ProfsDlg : public QDialog
{
    Q_OBJECT

    QGroupBox *horizontalGroupBox;
    QGroupBox *gridGroupBox;
    QDialogButtonBox *buttonBox;

    QPushButton* dirSelect;
    QLineEdit* dirEdit;
    void createHorizontalGroupBox();

    void createGridGroupBox();
    void populateProfile(void);
    void populateGui(void);

    std::shared_ptr<encryptor::Profile> _prof;

public:
    ProfsDlg(std::shared_ptr<encryptor::Profile>&, QWidget* parent = nullptr);

    inline const std::shared_ptr<encryptor::Profile>& GetProfile()
    {
        return _prof;
    }

private slots:
    void enableTargetDir(bool);
};

#endif
