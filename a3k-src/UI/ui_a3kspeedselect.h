/********************************************************************************
** Form generated from reading UI file 'a3kspeedselect.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_A3KSPEEDSELECT_H
#define UI_A3KSPEEDSELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_a3kSpeedSelect
{
public:
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *a3kSpeedSelect)
    {
        if (a3kSpeedSelect->objectName().isEmpty())
            a3kSpeedSelect->setObjectName(QStringLiteral("a3kSpeedSelect"));
        a3kSpeedSelect->resize(209, 102);
        lineEdit = new QLineEdit(a3kSpeedSelect);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 30, 181, 31));
        lineEdit->setMaxLength(3);
        lineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label = new QLabel(a3kSpeedSelect);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 191, 20));
        pushButton = new QPushButton(a3kSpeedSelect);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(60, 70, 91, 26));
        pushButton->setFlat(false);
        verticalLayoutWidget = new QWidget(a3kSpeedSelect);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 40, 160, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(a3kSpeedSelect);

        pushButton->setDefault(true);


        QMetaObject::connectSlotsByName(a3kSpeedSelect);
    } // setupUi

    void retranslateUi(QDialog *a3kSpeedSelect)
    {
        a3kSpeedSelect->setWindowTitle(QApplication::translate("a3kSpeedSelect", "Dialog", 0));
        lineEdit->setText(QApplication::translate("a3kSpeedSelect", "100", 0));
        label->setText(QApplication::translate("a3kSpeedSelect", "Value between 50 and 300", 0));
        pushButton->setText(QApplication::translate("a3kSpeedSelect", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class a3kSpeedSelect: public Ui_a3kSpeedSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_A3KSPEEDSELECT_H
