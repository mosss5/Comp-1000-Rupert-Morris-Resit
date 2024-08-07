/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *filePathEdit;
    QLineEdit *searchTermEdit;
    QCheckBox *regexCheckBox;
    QPushButton *searchButton;
    QTextEdit *resultsTextEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        filePathEdit = new QLineEdit(centralwidget);
        filePathEdit->setObjectName("filePathEdit");
        filePathEdit->setGeometry(QRect(160, 150, 113, 22));
        searchTermEdit = new QLineEdit(centralwidget);
        searchTermEdit->setObjectName("searchTermEdit");
        searchTermEdit->setGeometry(QRect(290, 150, 113, 22));
        regexCheckBox = new QCheckBox(centralwidget);
        regexCheckBox->setObjectName("regexCheckBox");
        regexCheckBox->setGeometry(QRect(500, 150, 131, 20));
        searchButton = new QPushButton(centralwidget);
        searchButton->setObjectName("searchButton");
        searchButton->setGeometry(QRect(410, 150, 75, 24));
        resultsTextEdit = new QTextEdit(centralwidget);
        resultsTextEdit->setObjectName("resultsTextEdit");
        resultsTextEdit->setGeometry(QRect(150, 190, 451, 181));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        filePathEdit->setText(QCoreApplication::translate("MainWindow", "file path", nullptr));
        searchTermEdit->setText(QCoreApplication::translate("MainWindow", "search term", nullptr));
        regexCheckBox->setText(QCoreApplication::translate("MainWindow", "regex option", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
