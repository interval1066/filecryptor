/********************************************************************************
** Form generated from reading UI file 'aboutdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDLG_H
#define UI_ABOUTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_AboutDlg
{
public:
    QFrame *frame;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_2;

    void setupUi(QDialog *AboutDlg)
    {
        if (AboutDlg->objectName().isEmpty())
            AboutDlg->setObjectName(QString::fromUtf8("AboutDlg"));
        AboutDlg->resize(392, 281);
        AboutDlg->setMouseTracking(false);
        AboutDlg->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 200, 200);"));
        frame = new QFrame(AboutDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 371, 261));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(14);
        frame->setMidLineWidth(3);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 20, 241, 41));
        QFont font;
        font.setPointSize(25);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(120, 160, 141, 20));
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 220, 301, 16));
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(100, 190, 181, 16));
        label_5->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(150, 80, 81, 71));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/res/data-encryption.png")));
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(AboutDlg);

        QMetaObject::connectSlotsByName(AboutDlg);
    } // setupUi

    void retranslateUi(QDialog *AboutDlg)
    {
        AboutDlg->setWindowTitle(QApplication::translate("AboutDlg", "Dialog", nullptr));
        label->setText(QApplication::translate("AboutDlg", "FileCryptor", nullptr));
        label_3->setText(QApplication::translate("AboutDlg", "\302\251 2021 Tim O'Neil", nullptr));
        label_4->setText(QApplication::translate("AboutDlg", "Simple per-item AES-256 Encryption Applicaiton", nullptr));
        label_5->setText(QApplication::translate("AboutDlg", "All Rights Reserved Forever", nullptr));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AboutDlg: public Ui_AboutDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDLG_H
