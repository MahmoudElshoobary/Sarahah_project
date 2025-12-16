#include "core.h"
#include <QDir>
#include <iostream>
#include <fstream>
#include <vector> // Ensure vector is included
#include <deque>  // Ensure deque is included

// ================= Message Implementation =================

QString Message::getFormattedTime() const {
    char buffer[80];
    struct tm lt;

#ifdef _MSC_VER
    if (localtime_s(&lt, &timestamp) != 0) {
        return "Time Error";
    }
#else
    struct tm* temp_lt = localtime(&timestamp);
    if (temp_lt == nullptr) {
        return "Time Error";
    }
    lt = *temp_lt;
#endif

    if (strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &lt) == 0) {
        return "Time Format Error";
    }
    return QString::fromStdString(std::string(buffer));
}

// ================= User Implementation =================

void User::addContact(const std::string &uname, int uid) {
    contacts[uname] = uid;
}

bool User::isContactID(int uid) const {
    for (const auto& pair : contacts) {
        if (pair.second == uid) {
            return true;
        }
    }
    return false;
}

void User::sendMessage(User& reciver, const std::string& text, bool isAnon) {
    Message m(id, reciver.id, text, isAnon);
    sent.push_back(m);
    reciver.received.push_back(m);
}

bool User::undoLastMessage(int receiverID, User& reciver) {
    if (sent.empty()) {
        return false;
    }

    if (sent.back().receiverID != receiverID) {
        return false;
    }

    Message m = sent.back();
    sent.pop_back();

    auto& rec = reciver.received;
    rec.erase(std::remove_if(rec.begin(), rec.end(), [&](const Message& msg) {
                  return msg.timestamp == m.timestamp && msg.text == m.text && msg.senderID == m.senderID;
              }),
              rec.end());

    return true;
}

bool User::addFavorite() {
    if (received.empty()) {
        return false;
    }
    // You should probably check if received is a deque or vector before using back()
    // Since it's a vector, back() is fine.
    favorites.push_back(received.back());
    return true;
}

bool User::removeOldestFavorite() {
    if (favorites.empty()) {
        return false;
    }
    favorites.pop_front();
    return true;
}

// File Handling (Kept as is, using std::fstream)
void User::loadFiles() {
    // Ensure the data directory exists
    QDir dir;
    std::string folder = "data";
    if (!dir.exists(QString::fromStdString(folder))) {
        dir.mkdir(QString::fromStdString(folder));
    }

    // --- 1. LOAD CONTACTS ---
    std::ifstream fcontacts(folder + "/user_" + std::to_string(id) + "_contacts.txt");
    if (fcontacts.is_open()) {
        std::string uname; int uid;
        while (fcontacts >> uname >> uid) {
            contacts[uname] = uid;
        }
        fcontacts.close();
    }

    // --- Message Loading Helper Lambdas ---
    // We need two lambdas to match the types: vector for sent/received, deque for favorites.

    // Helper for VECTOR containers (sent/received)
    auto loadVectorMessages = [&](const std::string& filename, std::vector<Message>& container) {
        std::ifstream file(filename);
        if (file.is_open()) {
            container.clear();
            Message msg;
            std::string line;

            while (std::getline(file, line)) {
                try { msg.senderID = std::stoi(line); } catch(...) { break; }

                if (!std::getline(file, line)) break;
                try { msg.receiverID = std::stoi(line); } catch(...) { break; }

                if (!std::getline(file, line)) break;
                try { msg.isAnonymous = (std::stoi(line) != 0); } catch(...) { break; }

                if (!std::getline(file, line)) break;
                try { msg.timestamp = std::stoll(line); } catch(...) { break; }

                if (!std::getline(file, msg.text)) break;

                container.push_back(msg);
            }
            file.close();
        }
    };

    // Helper for DEQUE containers (favorites)
    auto loadDequeMessages = [&](const std::string& filename, std::deque<Message>& container) {
        std::ifstream file(filename);
        if (file.is_open()) {
            container.clear();
            Message msg;
            std::string line;

            while (std::getline(file, line)) {
                try { msg.senderID = std::stoi(line); } catch(...) { break; }

                if (!std::getline(file, line)) break;
                try { msg.receiverID = std::stoi(line); } catch(...) { break; }

                if (!std::getline(file, line)) break;
                try { msg.isAnonymous = (std::stoi(line) != 0); } catch(...) { break; }

                if (!std::getline(file, line)) break;
                try { msg.timestamp = std::stoll(line); } catch(...) { break; }

                if (!std::getline(file, msg.text)) break;

                container.push_back(msg);
            }
            file.close();
        }
    };


    // --- 2. LOAD RECEIVED MESSAGES ---
    std::string receivedFile = folder + "/user_" + std::to_string(id) + "_received.txt";
    // FIX: Use loadVectorMessages for std::vector<Message>
    loadVectorMessages(receivedFile, received);

    // --- 3. LOAD SENT MESSAGES ---
    std::string sentFile = folder + "/user_" + std::to_string(id) + "_sent.txt";
    // FIX: Use loadVectorMessages for std::vector<Message>
    loadVectorMessages(sentFile, sent);

    // --- 4. LOAD FAVORITE MESSAGES ---
    std::string favFile = folder + "/user_" + std::to_string(id) + "_fav.txt";
    // FIX: Use loadDequeMessages for std::deque<Message>
    loadDequeMessages(favFile, favorites);
}

void User::saveFiles() {
    // Ensure the data directory exists
    QDir dir;
    std::string folder = "data";
    if (!dir.exists(QString::fromStdString(folder))) {
        dir.mkdir(QString::fromStdString(folder));
    }

    // --- 1. SAVE CONTACTS ---
    std::ofstream fcontacts(folder + "/user_" + std::to_string(id) + "_contacts.txt");
    if (fcontacts.is_open()) {
        for (const auto& c : contacts) {
            fcontacts << c.first << " " << c.second << "\n";
        }
        fcontacts.close();
    }

    // --- Message Saving Helper Lambda ---
    auto saveMessages = [&](const std::string& filename, const auto& container) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& msg : container) {
                file << msg.senderID << "\n";
                file << msg.receiverID << "\n";
                file << msg.isAnonymous << "\n";
                file << msg.timestamp << "\n";
                file << msg.text << "\n";
            }
            file.close();
        }
    };

    // --- 2. SAVE RECEIVED MESSAGES ---
    saveMessages(folder + "/user_" + std::to_string(id) + "_received.txt", received);

    // --- 3. SAVE SENT MESSAGES ---
    saveMessages(folder + "/user_" + std::to_string(id) + "_sent.txt", sent);

    // --- 4. SAVE FAVORITE MESSAGES ---
    saveMessages(folder + "/user_" + std::to_string(id) + "_fav.txt", favorites);
}

// ================= App Implementation =================

App::App(QObject *parent) : QObject(parent) {
    QDir dir;
    if (!dir.exists("data")) {
        dir.mkdir("data");
    }
    loadUsers();
}

User* App::getUserByID(int id) {
    if (users.count(id)) {
        return &users.at(id);
    }
    return nullptr;
}

User* App::getUserByUsername(const std::string& uname) {
    if (usernameToID.count(uname)) {
        return &users.at(usernameToID.at(uname));
    }
    return nullptr;
}

bool App::userExists(const std::string& uname) const {
    return usernameToID.count(uname);
}

bool App::registerUser(const std::string& uname, const std::string& pass) {
    if (userExists(uname)) {
        emit registrationFailed(QString("Username '%1' already exists.").arg(QString::fromStdString(uname)));
        return false;
    }
    if (uname.empty() || pass.empty()) {
        emit registrationFailed("Username and password cannot be empty.");
        return false;
    }

    users[nextUserID] = User(nextUserID, uname, pass);
    usernameToID[uname] = nextUserID;

    users[nextUserID].saveFiles();

    emit registrationSuccess(QString("Registration successful! Your ID: %1").arg(nextUserID));
    nextUserID++;
    saveUsers();
    return true;
}

User* App::login(const std::string& uname, const std::string& pass) {
    if (!userExists(uname)) {
        emit loginFailed("User not found.");
        return nullptr;
    }

    int id = usernameToID[uname];
    if (users.at(id).password != pass) {
        emit loginFailed("Wrong username or password.");
        return nullptr;
    }

    users.at(id).loadFiles();
    User* me = &users.at(id);

    emit loginSuccessful(me);
    return me;
}

void App::loadUsers() {
    std::ifstream f("data/users.txt");
    if (f.is_open()) {
        int id; std::string uname, pass;
        while (f >> id >> uname >> pass) {
            users[id] = User(id, uname, pass);
            usernameToID[uname] = id;
            if (id >= nextUserID) {
                nextUserID = id + 1;
            }
        }
        f.close();
    }
}

void App::saveUsers() {
    std::ofstream f("data/users.txt");
    for (auto& u : users)
        f << u.second.id << " " << u.second.username << " " << u.second.password << "\n";
    f.close();
}
