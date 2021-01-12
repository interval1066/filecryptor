#ifndef PWDLG_H
#define PWDLG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

class PWDialog : public QDialog
{
    Q_OBJECT

    void createFormGroupBox();

    enum { NumGridRows = 3, NumButtons = 4 };

    QGroupBox *formGroupBox;
    QTextEdit *smallEditor;
    QTextEdit *bigEditor;

    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];

    QDialogButtonBox *buttonBox;
    QMenu *fileMenu;
    QAction *exitAction;

public:
    PWDialog(QWidget *parent = nullptr);
};

#endif // PWDLG_H
