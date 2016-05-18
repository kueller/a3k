/********************************************************************************
** Form generated from reading UI file 'a3kconsole.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_A3KCONSOLE_H
#define UI_A3KCONSOLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_a3kconsole
{
public:
    QPlainTextEdit *console;

    void setupUi(QDialog *a3kconsole)
    {
        if (a3kconsole->objectName().isEmpty())
            a3kconsole->setObjectName(QStringLiteral("a3kconsole"));
        a3kconsole->resize(400, 300);
        console = new QPlainTextEdit(a3kconsole);
        console->setObjectName(QStringLiteral("console"));
        console->setGeometry(QRect(10, 10, 381, 281));
        QFont font;
        font.setFamily(QStringLiteral("DejaVu Sans Mono"));
        font.setPointSize(11);
        console->setFont(font);
        console->setLineWrapMode(QPlainTextEdit::WidgetWidth);

        retranslateUi(a3kconsole);

        QMetaObject::connectSlotsByName(a3kconsole);
    } // setupUi

    void retranslateUi(QDialog *a3kconsole)
    {
        a3kconsole->setWindowTitle(QApplication::translate("a3kconsole", "Console", 0));
    } // retranslateUi

};

namespace Ui {
    class a3kconsole: public Ui_a3kconsole {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_A3KCONSOLE_H
