/********************************************************************************
** Form generated from reading UI file 'a3kaddrdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_A3KADDRDIALOG_H
#define UI_A3KADDRDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_a3kaddrdialog
{
public:
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *a3kaddrdialog)
    {
        if (a3kaddrdialog->objectName().isEmpty())
            a3kaddrdialog->setObjectName(QStringLiteral("a3kaddrdialog"));
        a3kaddrdialog->resize(226, 70);
        lineEdit = new QLineEdit(a3kaddrdialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 10, 131, 25));
        pushButton = new QPushButton(a3kaddrdialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(150, 10, 71, 26));

        retranslateUi(a3kaddrdialog);

        QMetaObject::connectSlotsByName(a3kaddrdialog);
    } // setupUi

    void retranslateUi(QDialog *a3kaddrdialog)
    {
        a3kaddrdialog->setWindowTitle(QApplication::translate("a3kaddrdialog", "Jump to Address", 0));
        pushButton->setText(QApplication::translate("a3kaddrdialog", "Find", 0));
    } // retranslateUi

};

namespace Ui {
    class a3kaddrdialog: public Ui_a3kaddrdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_A3KADDRDIALOG_H
