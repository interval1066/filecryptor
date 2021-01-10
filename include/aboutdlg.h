#ifndef ABOUTDLG_H
#define ABOUTDLG_H

#include <QDialog>

namespace Ui {
class AboutDlg;
}

class AboutDlg : public QDialog
{
    Q_OBJECT
    bool eventFilter(QObject*, QEvent*);

public:
    explicit AboutDlg(QWidget* parent = nullptr);
    ~AboutDlg();

private:
    Ui::AboutDlg *ui;
};

#endif // ABOUTDLG_H
