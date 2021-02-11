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
    QString _pw;
    enum { NumGridRows = 3, NumButtons = 4 };

    QMenu*                  fileMenu;
    QGroupBox*              formGroupBox;
    QTextEdit*              smallEditor;

    QAction*                exitAction;
    QTextEdit*              bigEditor;
    QDialogButtonBox*       buttonBox;

    QLabel*                 labels[NumGridRows];
    QLineEdit*              lineEdit1;
    QLineEdit*              lineEdit2;
    QPushButton*            buttons[NumButtons];

    void createFormGroupBox(void);
    void accept(void) override;
    void reject(void) override;

public:
    explicit PWDialog(QWidget* parent = nullptr);
    const QString GetPW(void);
};

#endif // PWDLG_H
