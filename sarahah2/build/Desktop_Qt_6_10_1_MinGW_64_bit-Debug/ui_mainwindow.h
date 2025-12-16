/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QLabel *statusLabel;
    QLineEdit *usernameLineEdit;
    QLineEdit *lineEdit_2;
    QLabel *userLabel;
    QLabel *passlabel;
    QLabel *userLabel_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(140, 70, 501, 381));
        loginButton = new QPushButton(widget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(110, 270, 80, 24));
        loginButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        registerButton = new QPushButton(widget);
        registerButton->setObjectName("registerButton");
        registerButton->setGeometry(QRect(310, 270, 80, 24));
        registerButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        statusLabel = new QLabel(widget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setGeometry(QRect(100, 310, 261, 41));
        statusLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        usernameLineEdit = new QLineEdit(widget);
        usernameLineEdit->setObjectName("usernameLineEdit");
        usernameLineEdit->setGeometry(QRect(230, 130, 171, 24));
        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(230, 180, 171, 24));
        lineEdit_2->setEchoMode(QLineEdit::EchoMode::Password);
        userLabel = new QLabel(widget);
        userLabel->setObjectName("userLabel");
        userLabel->setGeometry(QRect(80, 120, 131, 41));
        userLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        passlabel = new QLabel(widget);
        passlabel->setObjectName("passlabel");
        passlabel->setGeometry(QRect(80, 170, 131, 41));
        passlabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        userLabel_2 = new QLabel(widget);
        userLabel_2->setObjectName("userLabel_2");
        userLabel_2->setGeometry(QRect(160, 40, 181, 71));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        userLabel_2->setFont(font);
        userLabel_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
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
        loginButton->setText(QCoreApplication::translate("MainWindow", "login", nullptr));
        registerButton->setText(QCoreApplication::translate("MainWindow", "register", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "status", nullptr));
        userLabel->setText(QCoreApplication::translate("MainWindow", "username", nullptr));
        passlabel->setText(QCoreApplication::translate("MainWindow", "password", nullptr));
        userLabel_2->setText(QCoreApplication::translate("MainWindow", "login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
