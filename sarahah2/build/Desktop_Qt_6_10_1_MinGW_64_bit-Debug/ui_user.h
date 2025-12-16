/********************************************************************************
** Form generated from reading UI file 'user.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER_H
#define UI_USER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_user
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QWidget *widget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *user)
    {
        if (user->objectName().isEmpty())
            user->setObjectName("user");
        user->resize(681, 450);
        stackedWidget = new QStackedWidget(user);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(180, 9, 481, 431));
        page = new QWidget();
        page->setObjectName("page");
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        widget = new QWidget(user);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 9, 120, 431));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(9, 30, 101, 24));
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 70, 101, 24));
        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 110, 101, 24));

        retranslateUi(user);

        QMetaObject::connectSlotsByName(user);
    } // setupUi

    void retranslateUi(QDialog *user)
    {
        user->setWindowTitle(QCoreApplication::translate("user", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("user", "contacts", nullptr));
        pushButton_2->setText(QCoreApplication::translate("user", "favorite msg", nullptr));
        pushButton_3->setText(QCoreApplication::translate("user", "msgs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class user: public Ui_user {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_H
