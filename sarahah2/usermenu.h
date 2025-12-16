#pragma once

#include <QDialog>
#include <QLabel>
#include <QListWidgetItem>
#include "core.h" // Or "user.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class UserMenu;
}
QT_END_NAMESPACE

class UserMenu : public QDialog
{
    Q_OBJECT

public:
    explicit UserMenu(User* user, App* app, QWidget *parent = nullptr);
    ~UserMenu();

private slots:
    // --- Navigation Slots (From the left menu buttons) ---
    void on_pushButton_clicked();    // "contacts" button
    void on_msg_tab_clicked();       // "msgs" button
    void on_fav_tab_clicked();       // "fav msgs" button
    void on_send_msg_tab_clicked();  // "send msg" button
    void on_logoutButtent_clicked(); // "logout" button

    // --- Contacts Page Slots ---
    void on_addcontact_btn_clicked();
   // void on_contact_list_itemClicked(QListWidgetItem *item);

    // --- Send Message Page Slots ---
    void on_sendButton_clicked();

    // --- Internal Methods ---
    void populateContactsList();
    void populateReceivedMessagesList();
   // void populateSendComboBox();
    void populateFavoriteMessagesList();
    void on_favoriteButton_clicked();

private:
    Ui::UserMenu *ui;
    App* m_app;
    User* m_currentUser;

    void setStatusMessage(QLabel* label, const QString& message, bool isError);
};
