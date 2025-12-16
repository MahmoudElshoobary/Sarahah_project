#pragma once

#include <QObject>
#include <QString>
#include <string>
#include <unordered_map>
#include <vector>
#include <deque> // We need this for favorites
#include <ctime>
#include <algorithm>

// ================= Message Class =================
class Message {
public:
    int senderID;
    int receiverID;
    time_t timestamp;
    std::string text;
    bool isAnonymous;

    Message() : isAnonymous(false) {}

    Message(int s, int r, const std::string& t, bool anon = false)
        : senderID(s), receiverID(r), timestamp(time(0)), text(t), isAnonymous(anon) {}

    QString getFormattedTime() const;
};

// Forward declaration of App class
class App;

// ================= User Class =================
class User {
public:
    int id;
    std::string username;
    std::string password;
    std::unordered_map<std::string, int> contacts;
    std::vector<Message> sent;     // KEEPING AS VECTOR
    std::vector<Message> received; // KEEPING AS VECTOR
    std::deque<Message> favorites; // KEEPING AS DEQUE

    User() {}
    User(int uid, const std::string& uname, const std::string& pass)
        : id(uid), username(uname), password(pass) {}

    // Public API Methods
    void addContact(const std::string &uname, int uid);
    bool isContactID(int uid) const;
    void sendMessage(User& reciver, const std::string& text, bool isAnon);
    bool undoLastMessage(int receiverID, User& reciver);
    bool addFavorite();
    bool removeOldestFavorite();

    // View/Getters for UI display
    const std::unordered_map<std::string, int>& getContacts() const { return contacts; }
    const std::vector<Message>& getSentMessages() const { return sent; }
    const std::vector<Message>& getReceivedMessages() const { return received; }
    const std::deque<Message>& getFavoriteMessages() const { return favorites; }

    // File Handling
    void loadFiles();
    void saveFiles();
};


// ================= App Class (The QObject Model) =================
class App : public QObject {
    Q_OBJECT

private:
    std::unordered_map<int, User> users;
    std::unordered_map<std::string, int> usernameToID;
    int nextUserID = 1;

public:
    explicit App(QObject *parent = nullptr);

    // Public API Methods
    const std::unordered_map<int, User>& getUsers() const { return users; }
    User* getUserByID(int id);
    User* getUserByUsername(const std::string& uname);

    // Logic methods that return status instead of printing
    bool userExists(const std::string& uname) const;
    bool registerUser(const std::string& uname, const std::string& pass);
    User* login(const std::string& uname, const std::string& pass);

    // File Handling
    void loadUsers();
    void saveUsers();

signals:
    // Global events
    void loginSuccessful(User* loggedInUser);
    void loginFailed(const QString& reason);
    void registrationSuccess(const QString& username);
    void registrationFailed(const QString& reason);

    // User-specific events
    void messagesUpdated(int userID);
};
