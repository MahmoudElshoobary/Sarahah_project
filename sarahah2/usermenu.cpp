#include "usermenu.h"
#include "ui_usermenu.h"
#include "mainwindow.h"

#include "core.h"          // Your core model containing App and User classes
#include <QMessageBox>     // For user feedback on actions
#include <QListWidgetItem> // For working with QListWidget
#include <QVariant>        // Used for storing int ID in QComboBox data
#include <QDebug>          // Helpful for debugging (optional)

// Helper function to set status messages (reusable for add_status, etc.)
void UserMenu::setStatusMessage(QLabel* label, const QString& message, bool isError)
{
    QString style = isError ? "color: red;" : "color: green;";
    label->setText(message);
    label->setStyleSheet(style);
}

// =================================================================
// CONSTRUCTOR / DESTRUCTOR
// =================================================================

// FIX: Constructor signature and initialization now match the header (QDialog)
UserMenu::UserMenu(User* user, App* app, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserMenu)
    , m_app(app)
    , m_currentUser(user)
{
    ui->setupUi(this);

    if (m_currentUser) {
        setWindowTitle("Saraha - Welcome " + QString::fromStdString(m_currentUser->username));
    }

    // Call population functions right after setupUi
    populateContactsList();
    populateReceivedMessagesList();
    populateFavoriteMessagesList(); // Assuming you'll implement this soon
}

UserMenu::~UserMenu()
{
    delete ui;
}

// =================================================================
// NAVIGATION SLOTS (Left Menu Buttons)
// =================================================================

void UserMenu::on_pushButton_clicked()     // "contacts" button
{
    ui->stackedWidget->setCurrentIndex(0);
    populateContactsList(); // Refresh the list
}

void UserMenu::on_msg_tab_clicked()        // "msgs" button
{
    ui->stackedWidget->setCurrentIndex(1);
    populateReceivedMessagesList(); // Refresh the list
}

void UserMenu::on_fav_tab_clicked()        // "fav msgs" button
{
    ui->stackedWidget->setCurrentIndex(2);
    populateFavoriteMessagesList(); // Refresh the list
}

void UserMenu::on_send_msg_tab_clicked()   // "send msg" button
{
    ui->stackedWidget->setCurrentIndex(3);
    // The combo box is populated in populateContactsList, so just switching is fine.
}

void UserMenu::on_logoutButtent_clicked()  // "logout" button
{
    // The previous window (MainWindow) should handle re-opening the login screen


    this->close();
}

// =================================================================
// PAGE 0: CONTACTS LOGIC (Display and Add)
// =================================================================

void UserMenu::populateContactsList()
{
    ui->contact_list->clear();
    ui->comboBox->clear();

    if (!m_currentUser) return;

    // Add a placeholder to the combobox first
    ui->comboBox->addItem("Select Contact", 0);

    for (const auto& pair : m_currentUser->contacts) {
        QString name = QString::fromStdString(pair.first);
        int id = pair.second;
        QString display = QString("%1 (ID: %2)").arg(name).arg(id);

        QListWidgetItem *item = new QListWidgetItem(display);
        item->setData(Qt::UserRole + 1, id);
        ui->contact_list->addItem(item);

        // Populate the send message combo box
        ui->comboBox->addItem(name, id);
    }
}

void UserMenu::on_addcontact_btn_clicked()
{
    QString unameQ = ui->addContactLinEdit->text();
    std::string uname = unameQ.toStdString();

    if (uname.empty()) {
        setStatusMessage(ui->add_status, "Username cannot be empty.", true);
        return;
    }

    if (m_app->userExists(uname)) {
        User* targetUser = m_app->getUserByUsername(uname);
        if (targetUser->id == m_currentUser->id) {
            setStatusMessage(ui->add_status, "Cannot add yourself as a contact.", true);
        } else {
            // Check if contact already exists before adding
            if (m_currentUser->contacts.count(uname)) {
                setStatusMessage(ui->add_status, QString("%1 is already in your contacts.").arg(unameQ), true);
            } else {
                m_currentUser->addContact(uname, targetUser->id);
                m_currentUser->saveFiles();
                populateContactsList();
                setStatusMessage(ui->add_status, QString("%1 added successfully!").arg(unameQ), false);
            }
        }
    } else {
        setStatusMessage(ui->add_status, QString("User '%1' not found.").arg(unameQ), true);
    }
    ui->addContactLinEdit->clear();
}

// =================================================================
// PAGE 1: RECEIVED MESSAGES LOGIC (Display)
// =================================================================

void UserMenu::populateReceivedMessagesList()
{
    ui->msg_list->clear();
    if (!m_currentUser) return;

    // Iterate backwards to show newest messages first
    for (auto it = m_currentUser->received.rbegin(); it != m_currentUser->received.rend(); ++it) {
        const Message& msg = *it;

        // 1. Get sender name
        QString senderName;
        if (msg.isAnonymous) {
            senderName = "Anonymous";
        } else {
            User* sender = m_app->getUserByID(msg.senderID);
            senderName = sender ? QString::fromStdString(sender->username) : "Unknown User";
        }

        // 2. Format display text
        QString displayText = QString("[%1] %2: %3")
                                  .arg(msg.getFormattedTime())
                                  .arg(senderName)
                                  .arg(QString::fromStdString(msg.text).left(100) + (msg.text.length() > 100 ? "..." : ""));

        QListWidgetItem *item = new QListWidgetItem(displayText);
        ui->msg_list->addItem(item);
    }
}

// =================================================================
// PAGE 2: FAVORITE MESSAGES LOGIC (Display)
// =================================================================

void UserMenu::populateFavoriteMessagesList()
{
    ui->fav_msg_list->clear();
    if (!m_currentUser) return;

    // Iterate through the favorites (QDeque)
    for (const Message& msg : m_currentUser->favorites) {

        // 1. Get sender name
        QString senderName;
        if (msg.isAnonymous) {
            senderName = "Anonymous";
        } else {
            User* sender = m_app->getUserByID(msg.senderID);
            senderName = sender ? QString::fromStdString(sender->username) : "Unknown User";
        }

        // 2. Format display text
        QString displayText = QString("[%1] %2: %3 (FAVORITE)")
                                  .arg(msg.getFormattedTime())
                                  .arg(senderName)
                                  .arg(QString::fromStdString(msg.text).left(100) + (msg.text.length() > 100 ? "..." : ""));

        QListWidgetItem *item = new QListWidgetItem(displayText);
        ui->fav_msg_list->addItem(item);
    }
}

// Note: To implement the 'Add to Favorite' button, you need a button
// on the 'msgs' page (Index 1). Assuming you add a button named 'favoriteButton'
// that slot would look like the one discussed previously:

void UserMenu::on_favoriteButton_clicked()
{
    if (m_currentUser && m_currentUser->addFavorite()) {
        m_currentUser->saveFiles();
        populateFavoriteMessagesList(); // Refresh list
        QMessageBox::information(this, "Success", "Last received message added to favorites.");
    } else {
        QMessageBox::warning(this, "Error", "No message to add to favorites.");
    }
}



// =================================================================
// PAGE 3: SEND MESSAGE LOGIC
// =================================================================

void UserMenu::on_sendButton_clicked()
{
    // 1. Get receiver ID from ComboBox data
    int receiverID = ui->comboBox->currentData(Qt::UserRole).toInt();
    QString receiverName = ui->comboBox->currentText();

    // 2. Get message text and anonymity status
    std::string msgText = ui->MsgSendBox->text().toStdString();
    bool isAnon = ui->is_annon->isChecked();

    if (receiverID <= 0) {
        QMessageBox::warning(this, "Error", "Please select a valid contact.");
        return;
    }
    if (msgText.empty()) {
        QMessageBox::warning(this, "Error", "Message cannot be empty.");
        return;
    }

    // 3. Call core logic
    User* receiver = m_app->getUserByID(receiverID);
    if (receiver) {

        receiver->loadFiles();

        m_currentUser->sendMessage(*receiver, msgText, isAnon);

        // IMPORTANT: Save both the sender's data and the receiver's data
        m_currentUser->saveFiles();
        receiver->saveFiles();

        QMessageBox::information(this, "Success",
                                 QString("Message sent to %1 %2.").arg(receiverName).arg(isAnon ? "(Anonymously)" : ""));

        // Clear inputs after sending
        ui->MsgSendBox->clear();
        ui->is_annon->setChecked(false);
    } else {
        QMessageBox::critical(this, "Error", "Receiver user not found in database.");
    }
}
