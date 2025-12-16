/********************************************************************************
** Form generated from reading UI file 'usermenu.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMENU_H
#define UI_USERMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserMenu
{
public:
    QStackedWidget *stackedWidget;
    QWidget *contacts;
    QListWidget *contact_list;
    QLabel *label_3;
    QLineEdit *addContactLinEdit;
    QLabel *label_4;
    QPushButton *addcontact_btn;
    QLabel *add_status;
    QWidget *msgs;
    QListWidget *msg_list;
    QPushButton *favoriteButton;
    QWidget *favmsg;
    QListWidget *fav_msg_list;
    QWidget *send_msg;
    QPushButton *sendButton;
    QCheckBox *is_annon;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QLineEdit *MsgSendBox;
    QWidget *widget;
    QPushButton *pushButton;
    QPushButton *msg_tab;
    QPushButton *logoutButtent;
    QPushButton *fav_tab;
    QPushButton *send_msg_tab;

    void setupUi(QDialog *UserMenu)
    {
        if (UserMenu->objectName().isEmpty())
            UserMenu->setObjectName("UserMenu");
        UserMenu->resize(681, 476);
        stackedWidget = new QStackedWidget(UserMenu);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(170, 20, 481, 431));
        contacts = new QWidget();
        contacts->setObjectName("contacts");
        contact_list = new QListWidget(contacts);
        contact_list->setObjectName("contact_list");
        contact_list->setGeometry(QRect(0, 100, 481, 331));
        label_3 = new QLabel(contacts);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 70, 61, 21));
        addContactLinEdit = new QLineEdit(contacts);
        addContactLinEdit->setObjectName("addContactLinEdit");
        addContactLinEdit->setGeometry(QRect(0, 30, 341, 24));
        label_4 = new QLabel(contacts);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 10, 91, 21));
        addcontact_btn = new QPushButton(contacts);
        addcontact_btn->setObjectName("addcontact_btn");
        addcontact_btn->setGeometry(QRect(370, 30, 101, 24));
        add_status = new QLabel(contacts);
        add_status->setObjectName("add_status");
        add_status->setGeometry(QRect(260, 70, 171, 21));
        stackedWidget->addWidget(contacts);
        msgs = new QWidget();
        msgs->setObjectName("msgs");
        msg_list = new QListWidget(msgs);
        msg_list->setObjectName("msg_list");
        msg_list->setGeometry(QRect(0, 40, 481, 391));
        favoriteButton = new QPushButton(msgs);
        favoriteButton->setObjectName("favoriteButton");
        favoriteButton->setGeometry(QRect(190, 10, 101, 24));
        stackedWidget->addWidget(msgs);
        favmsg = new QWidget();
        favmsg->setObjectName("favmsg");
        fav_msg_list = new QListWidget(favmsg);
        fav_msg_list->setObjectName("fav_msg_list");
        fav_msg_list->setGeometry(QRect(0, 0, 481, 431));
        stackedWidget->addWidget(favmsg);
        send_msg = new QWidget();
        send_msg->setObjectName("send_msg");
        sendButton = new QPushButton(send_msg);
        sendButton->setObjectName("sendButton");
        sendButton->setGeometry(QRect(200, 360, 271, 71));
        is_annon = new QCheckBox(send_msg);
        is_annon->setObjectName("is_annon");
        is_annon->setGeometry(QRect(30, 360, 131, 71));
        is_annon->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        is_annon->setIconSize(QSize(32, 32));
        is_annon->setChecked(false);
        label = new QLabel(send_msg);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 70, 81, 16));
        comboBox = new QComboBox(send_msg);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(20, 30, 451, 31));
        label_2 = new QLabel(send_msg);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 10, 81, 16));
        MsgSendBox = new QLineEdit(send_msg);
        MsgSendBox->setObjectName("MsgSendBox");
        MsgSendBox->setGeometry(QRect(20, 100, 441, 251));
        stackedWidget->addWidget(send_msg);
        widget = new QWidget(UserMenu);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 10, 120, 431));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(9, 30, 101, 24));
        msg_tab = new QPushButton(widget);
        msg_tab->setObjectName("msg_tab");
        msg_tab->setGeometry(QRect(10, 70, 101, 24));
        logoutButtent = new QPushButton(widget);
        logoutButtent->setObjectName("logoutButtent");
        logoutButtent->setGeometry(QRect(10, 390, 101, 24));
        fav_tab = new QPushButton(widget);
        fav_tab->setObjectName("fav_tab");
        fav_tab->setGeometry(QRect(10, 110, 101, 24));
        send_msg_tab = new QPushButton(widget);
        send_msg_tab->setObjectName("send_msg_tab");
        send_msg_tab->setGeometry(QRect(10, 250, 101, 24));

        retranslateUi(UserMenu);

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(UserMenu);
    } // setupUi

    void retranslateUi(QDialog *UserMenu)
    {
        UserMenu->setWindowTitle(QCoreApplication::translate("UserMenu", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("UserMenu", "contacts", nullptr));
        label_4->setText(QCoreApplication::translate("UserMenu", "add contact", nullptr));
        addcontact_btn->setText(QCoreApplication::translate("UserMenu", "add", nullptr));
        add_status->setText(QCoreApplication::translate("UserMenu", "status of add", nullptr));
        favoriteButton->setText(QCoreApplication::translate("UserMenu", "add to fav", nullptr));
        sendButton->setText(QCoreApplication::translate("UserMenu", "send msg", nullptr));
        is_annon->setText(QCoreApplication::translate("UserMenu", "annonemes", nullptr));
        label->setText(QCoreApplication::translate("UserMenu", "your msg", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("UserMenu", "kamel", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("UserMenu", "wade3", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("UserMenu", "mahmoud", nullptr));

        label_2->setText(QCoreApplication::translate("UserMenu", "choose contact", nullptr));
        pushButton->setText(QCoreApplication::translate("UserMenu", "contacts", nullptr));
        msg_tab->setText(QCoreApplication::translate("UserMenu", "msgs", nullptr));
        logoutButtent->setText(QCoreApplication::translate("UserMenu", "logout", nullptr));
        fav_tab->setText(QCoreApplication::translate("UserMenu", "fav msgs", nullptr));
        send_msg_tab->setText(QCoreApplication::translate("UserMenu", "send msg", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserMenu: public Ui_UserMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMENU_H
