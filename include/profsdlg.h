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
    encryptor::Profile* _prof;

public:
    ProfsDlg(encryptor::Profile* prof, QWidget *parent = nullptr);

private slots:
    void enableTargetDir(bool);
};

#endif
