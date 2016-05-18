/********************************************************************************
** Form generated from reading UI file 'a3k.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_A3K_H
#define UI_A3K_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_a3k
{
public:
    QAction *actionLoad_File;
    QAction *actionJump_to_Address;
    QAction *actionJump_To_Address;
    QAction *actionShow_Console;
    QAction *actionExit;
    QAction *actionSet_Speed;
    QWidget *centralWidget;
    QListWidget *memList;
    QListWidget *regList;
    QLabel *statusLabel;
    QPushButton *runButton;
    QPushButton *runFastButton;
    QPushButton *stepButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOptions;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *a3k)
    {
        if (a3k->objectName().isEmpty())
            a3k->setObjectName(QStringLiteral("a3k"));
        a3k->resize(591, 418);
        actionLoad_File = new QAction(a3k);
        actionLoad_File->setObjectName(QStringLiteral("actionLoad_File"));
        actionJump_to_Address = new QAction(a3k);
        actionJump_to_Address->setObjectName(QStringLiteral("actionJump_to_Address"));
        actionJump_To_Address = new QAction(a3k);
        actionJump_To_Address->setObjectName(QStringLiteral("actionJump_To_Address"));
        actionShow_Console = new QAction(a3k);
        actionShow_Console->setObjectName(QStringLiteral("actionShow_Console"));
        actionExit = new QAction(a3k);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSet_Speed = new QAction(a3k);
        actionSet_Speed->setObjectName(QStringLiteral("actionSet_Speed"));
        centralWidget = new QWidget(a3k);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        memList = new QListWidget(centralWidget);
        memList->setObjectName(QStringLiteral("memList"));
        memList->setGeometry(QRect(400, 20, 181, 331));
        QFont font;
        font.setFamily(QStringLiteral("DejaVu Sans Mono"));
        memList->setFont(font);
        regList = new QListWidget(centralWidget);
        regList->setObjectName(QStringLiteral("regList"));
        regList->setGeometry(QRect(10, 20, 151, 301));
        regList->setFont(font);
        statusLabel = new QLabel(centralWidget);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setGeometry(QRect(10, 330, 191, 16));
        runButton = new QPushButton(centralWidget);
        runButton->setObjectName(QStringLiteral("runButton"));
        runButton->setGeometry(QRect(230, 40, 91, 26));
        runFastButton = new QPushButton(centralWidget);
        runFastButton->setObjectName(QStringLiteral("runFastButton"));
        runFastButton->setGeometry(QRect(230, 80, 91, 26));
        stepButton = new QPushButton(centralWidget);
        stepButton->setObjectName(QStringLiteral("stepButton"));
        stepButton->setGeometry(QRect(230, 120, 91, 26));
        pauseButton = new QPushButton(centralWidget);
        pauseButton->setObjectName(QStringLiteral("pauseButton"));
        pauseButton->setGeometry(QRect(230, 160, 91, 26));
        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setGeometry(QRect(230, 200, 91, 26));
        a3k->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(a3k);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 591, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        a3k->setMenuBar(menuBar);
        mainToolBar = new QToolBar(a3k);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        a3k->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(a3k);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        a3k->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuFile->addAction(actionLoad_File);
        menuFile->addAction(actionExit);
        menuOptions->addAction(actionJump_To_Address);
        menuOptions->addAction(actionSet_Speed);
        menuOptions->addAction(actionShow_Console);

        retranslateUi(a3k);

        QMetaObject::connectSlotsByName(a3k);
    } // setupUi

    void retranslateUi(QMainWindow *a3k)
    {
        a3k->setWindowTitle(QApplication::translate("a3k", "a3k", 0));
        actionLoad_File->setText(QApplication::translate("a3k", "Load File", 0));
        actionJump_to_Address->setText(QApplication::translate("a3k", "Jump to Address", 0));
        actionJump_To_Address->setText(QApplication::translate("a3k", "Jump To Address", 0));
        actionShow_Console->setText(QApplication::translate("a3k", "Show Console", 0));
        actionExit->setText(QApplication::translate("a3k", "Exit", 0));
        actionSet_Speed->setText(QApplication::translate("a3k", "Set Execute Period", 0));
        statusLabel->setText(QApplication::translate("a3k", "No file loaded.", 0));
        runButton->setText(QApplication::translate("a3k", "Run", 0));
        runFastButton->setText(QApplication::translate("a3k", "Run Fast", 0));
        stepButton->setText(QApplication::translate("a3k", "Step", 0));
        pauseButton->setText(QApplication::translate("a3k", "Pause", 0));
        stopButton->setText(QApplication::translate("a3k", "Stop/Reset", 0));
        menuFile->setTitle(QApplication::translate("a3k", "File", 0));
        menuOptions->setTitle(QApplication::translate("a3k", "Options", 0));
    } // retranslateUi

};

namespace Ui {
    class a3k: public Ui_a3k {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_A3K_H
