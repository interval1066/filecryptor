#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QPushButton;
class QTextEdit;
class QCheckBox;
QT_END_NAMESPACE

class ProfsDlg : public QDialog
{
    Q_OBJECT

public:
    ProfsDlg();

private:
    void createHorizontalGroupBox();
    void createGridGroupBox();

    enum { NumGridRows = 3, NumButtons = 4 };

    QGroupBox *horizontalGroupBox;
    QGroupBox *gridGroupBox;
    QTextEdit *smallEditor;
    QCheckBox* saveOriginal;
    QTextEdit *bigEditor;
    QLabel *labels[NumGridRows];
    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;
};

#endif // DIALOG_H
