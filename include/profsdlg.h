#ifndef PROFSDLG_H_
#define PROFSDLG_H_

#include <QDialog>

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

    void createHorizontalGroupBox();
    void createGridGroupBox();

    enum { NumGridRows = 3, NumButtons = 4 };

    QGroupBox *horizontalGroupBox;
    QGroupBox *gridGroupBox;
    QLabel *labels[NumGridRows];

    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;
    QPushButton* dirSelect;

    QLineEdit* dirEdit;

public:
    ProfsDlg();

private slots:
    void enableTargetDir(bool);
};

#endif
