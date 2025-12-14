#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>
#include <string>
#include <limits> 
using namespace std;
// ================= Message Class =================
class Message {
public:
    int senderID;
    int receiverID;
    time_t timestamp;
    string text;
    bool isAnonymous;

    Message() : isAnonymous(false) {}
    Message(int s, int r, const string& t, bool anon = false)
        : senderID(s), receiverID(r), timestamp(time(0)), text(t), isAnonymous(anon) {}
    string getFormattedTime() const {
        char buffer[80];

        // 1. Declare the struct tm object locally
        struct tm lt;

        // 2. Use localtime_s instead of localtime
        // Note: localtime_s signature is different: 
        // errno_t localtime_s(struct tm* _Tm, const time_t* _Time)
        if (localtime_s(&lt, &timestamp) != 0) {
            // Error handling, though unlikely to fail here
            return "Time Error";
        }

        // 3. Pass the address of your local struct tm object to strftime
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &lt);
        return string(buffer);
    }
};

class App;

class User {

public:
    int id;
    string username;
    string password;
    unordered_map<string, int> contacts;
    vector<Message> sent;
    vector<Message> received;
    deque<Message> favorites;

    User() {}
    User(int uid, const string& uname, const string& pass)
        : id(uid), username(uname), password(pass) {}

    void addContact(const string & uname,int uid) {
        contacts[uname] = uid;
    }
    bool isContactID(int uid) {
        for (const auto& pair : contacts) {
            if (pair.second == uid) {
                return true;
            }
        }
        return false;
    }
    void sendMessage(User& reciver, const string& text, bool isAnon) {
        Message m(id, reciver.id, text, isAnon);
        sent.push_back(m);
        reciver.received.push_back(m);
    }

    void undoLastMessage(User& reciver) {
        if (sent.empty()) {
            cout << "you haven't sent any messages";
            return;
        }
        Message m = sent.back();
        sent.pop_back();

        auto& rec = reciver.received;
        rec.erase(remove_if(rec.begin(), rec.end(), [&](Message msg) {
            return msg.timestamp == m.timestamp && msg.text == m.text;
            }),
            rec.end());
        cout << "last mesage deleted.\n";
    }

    void addFavorite() {
        if (!received.empty()) {
            favorites.push_back(received.back());
            cout << "Last received message added to favorites.\n";
        }
        else {
            cout << "No received messages.\n";
        }
    }
    void removeOldestFavorite() {
        if (!favorites.empty()) {
            favorites.pop_front();
            cout << "Oldest favorite removed.\n";
        }
        else {
            cout << "No favorites to remove.\n";
        }
    }

    void viewContacts() {
        if (contacts.empty()) {
            cout << "No contacts.\n";
            return;
        }
        cout << "Contacts:\n";
        for (auto& c : contacts)
            cout << "- " << c.first << " (ID: " << c.second << ")\n";
    }

    void viewSent() {
        if (sent.empty()) {
            cout << "No sent messages.\n";
            return;
        }
        cout << "Sent Messages (latest first):\n";
        for (int i = sent.size() - 1; i >= 0; i--) {
            cout << "[" << sent[i].getFormattedTime() << "] ";
            cout << "To ID " << sent[i].receiverID << ": " << sent[i].text;
            cout << (sent[i].isAnonymous ? " (Sent Anonymously)\n" : "\n");
        }
    }

    void viewReceivedFrom(int senderID, const unordered_map<int, User>& users) {
        bool found = false;

        for (const auto& m : received) {
            if (m.senderID == senderID) {

                
                if (m.isAnonymous) {
                    continue;
                }

                cout << "[" << m.getFormattedTime() << "] ";

                cout << users.at(senderID).username << ": " << m.text << "\n";

                found = true;
            }
        }
        if (!found) cout << "No defined messages found from this contact.\n";
    }



    void viewAllReceived(const unordered_map<int, User>& users) {
        if (received.empty()) { cout << "No received messages.\n"; return; }
        cout << "Received Messages (latest first):\n";

        unordered_map<int, bool> is_contact_map;
        for (const auto& pair : contacts) {
            
            int id = pair.second;
            is_contact_map[id] = true;
        }

        for (int i = received.size() - 1; i >= 0; --i) {
            const Message& m = received[i];
            cout << "[" << m.getFormattedTime() << "] ";

            bool isContact = is_contact_map.count(m.senderID);

            if (m.isAnonymous || !isContact) {
                cout << "Sender ID " << m.senderID << (m.isAnonymous ? " (Anonymous)" : "") << ": " << m.text << "\n";
            }
            else {
                cout << users.at(m.senderID).username << ": " << m.text << "\n";
            }
        }
    }

    void viewFavorites() {
        if (favorites.empty())
        {
            cout << "No favorite messages.\n";
            return;
        }
        cout << "Favorite Messages:\n";
        for (auto& m : favorites) {
            cout << m.text << " (From ID: " << m.senderID << ", Anonymous: " << (m.isAnonymous ? "Yes" : "No") << ")\n";
        }
    }
    //  File Handling -->>save and loadfiles
    void loadFiles() {
        string folder = "data";
        ifstream fcontacts(folder + "/user_" + to_string(id) + "_contacts.txt");
        if (fcontacts.is_open()) {
            string uname; int uid;
            while (fcontacts >> uname >> uid)
                contacts[uname] = uid;
            fcontacts.close();
        }
        ifstream fsent(folder + "/user_" + to_string(id) + "_sent.txt");
        if (fsent.is_open()) {
            int s, r, anon_int; time_t t; string line;
            while (fsent >> s >> r >> t >> anon_int) {
                getline(fsent, line);
                getline(fsent, line);
                Message msg(s, r, line);
                msg.timestamp = t;
                msg.isAnonymous = (anon_int == 1);
                sent.push_back(msg);
            }
            fsent.close();
        }
        ifstream frec(folder + "/user_" + to_string(id) + "_received.txt");
        if (frec.is_open()) {
            int s, r, anon_int; time_t t; string line;
            while (frec >> s >> r >> t >> anon_int) {
                getline(frec, line);
                getline(frec, line);
                Message msg(s, r, line);
                msg.timestamp = t;
                msg.isAnonymous = (anon_int == 1);
                received.push_back(msg);
            }
            frec.close();
        }
        ifstream ffav(folder + "/user_" + to_string(id) + "_fav.txt");
        if (ffav.is_open()) {
            int s, r, anon_int; time_t t; string line;
            while (ffav >> s >> r >> t >> anon_int) {
                getline(ffav, line);
                getline(ffav, line);
                Message msg(s, r, line);
                msg.timestamp = t;
                msg.isAnonymous = (anon_int == 1);
                favorites.push_back(msg);
            }
            ffav.close();
        }
    }

    void saveFiles() {
        string folder = "data";
        ofstream fcontacts(folder + "/user_" + to_string(id) + "_contacts.txt");
        for (auto& c : contacts)
            fcontacts << c.first << " " << c.second << "\n";
        fcontacts.close();

        ofstream fsent(folder + "/user_" + to_string(id) + "_sent.txt");
        for (auto& m : sent)
            fsent << m.senderID << " " << m.receiverID << " " << m.timestamp << " " << (m.isAnonymous ? 1 : 0) << "\n" << m.text << "\n";
        fsent.close();

        ofstream frec(folder + "/user_" + to_string(id) + "_received.txt");
        for (auto& m : received)
            frec << m.senderID << " " << m.receiverID << " " << m.timestamp << " " << (m.isAnonymous ? 1 : 0) << "\n" << m.text << "\n";
        frec.close();

        ofstream ffav(folder + "/user_" + to_string(id) + "_fav.txt");
        for (auto& m : favorites)
            ffav << m.senderID << " " << m.receiverID << " " << m.timestamp << " " << (m.isAnonymous ? 1 : 0) << "\n" << m.text << "\n";
        ffav.close();
    }

};
class App {
private:
    unordered_map<int, User> users;
    unordered_map<string, int> usernameToID;
    int nextUserID = 1;

public:
    App() {
        loadUsers();
    }

    const unordered_map<int, User>& getUsers() const {
        return users;
    }

    void loadUsers() {
        ifstream f("data/users.txt");
        if (f.is_open()) {
            int id; string uname, pass;
            while (f >> id >> uname >> pass) {
                users[id] = User(id, uname, pass);
                usernameToID[uname] = id;
                nextUserID = max(nextUserID, id + 1);
            }
            f.close();
        }
    }

    void saveUsers() {
        ofstream f("data/users.txt");
        for (auto& u : users)
            f << u.second.id << " " << u.second.username << " " << u.second.password << "\n";
        f.close();
    }

    void registerUser() {
        string uname, pass;
        cout << "Enter username: "; cin >> uname;
        if (usernameToID.count(uname)) { cout << "Username exists!\n"; return; }
        cout << "Enter password: "; cin >> pass;

        users[nextUserID] = User(nextUserID, uname, pass);
        usernameToID[uname] = nextUserID;
        users[nextUserID].saveFiles();
        cout << "Registered successfully! Your ID: " << nextUserID << "\n";
        nextUserID++;
        saveUsers();
    }

    User* login() {
        string uname, pass;
        cout << "Enter username: "; cin >> uname;
        cout << "Enter password: "; cin >> pass;
        if (!usernameToID.count(uname)) return nullptr;
        int id = usernameToID[uname];
        if (users[id].password != pass) return nullptr;

        users[id].loadFiles();
        cout << "Logged in successfully!\n";
        return &users[id];
    }

    void run() {
        while (true) {
            cout << "\n===== Modified Saraha (Anonymous Enabled) =====\n";
            cout << "1- Register\n2- Login\n3- Exit\nChoose: ";
            int ch;
            if (!(cin >> ch)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please try again.\n";
                continue;
            }

            if (ch == 3) { cout << "Goodbye!\n"; break; }

            if (ch == 1) registerUser();
            else if (ch == 2) {
                User* me = login();
                if (!me) { cout << "Wrong username/password.\n"; continue; }

                while (true) {
                    cout << "\n--- User Menu (" << me->username << ") ---\n";
                    cout << "1 Add Contact\n2 Send Message\n3 Undo Last\n4 View Contacts\n";
                    cout << "5 View Sent\n6 View Received From Contact (Only Known Messages)\n"; // ?? ????? ????
                    cout << "7 Add Favorite\n8 Remove Oldest Favorite\n9 View Favorites\n10 View All Received\n0 Logout\nChoose: ";

                    if (!(cin >> ch)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please try again.\n";
                        continue;
                    }

                    if (ch == 0) {
                        me->saveFiles();
                        saveUsers();
                        cout << "Logged out.\n";
                        break;
                    }

                    if (ch == 1) {
                        string cname;
                        cout << "Enter contact username: "; cin >> cname;
                        if (!usernameToID.count(cname)) { cout << "User not found!\n"; continue; }
                        int cid = usernameToID[cname];
                        me->addContact(cname, cid);
                        cout << "Contact added.\n";
                    }
                    else if (ch == 2) {
                        string rname;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter receiver username: "; getline(cin, rname);
                        if (!usernameToID.count(rname)) { cout << "User not found!\n"; continue; }
                        int rid = usernameToID[rname];

                        cout << "Send as (1) Known / (2) Unknown? [1/2]: ";
                        int anon_choice;
                        if (!(cin >> anon_choice)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid choice. Sending as Known.\n";
                            anon_choice = 1;
                        }
                        bool isAnonymous = (anon_choice == 2);

                        string msg;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter message: "; getline(cin, msg);

                        me->sendMessage(users[rid], msg, isAnonymous);
                        cout << "Message sent" << (isAnonymous ? " (Anonymously)" : "") << ".\n";
                    }
                    else if (ch == 3) {
                        string rname;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter receiver username to undo last: "; getline(cin, rname);
                        if (!usernameToID.count(rname)) { cout << "User not found!\n"; continue; }
                        int rid = usernameToID[rname];
                        me->undoLastMessage(users[rid]);
                    }
                    else if (ch == 4) me->viewContacts();
                    else if (ch == 5) me->viewSent();
                    else if (ch == 6) {
                        string cname;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter contact username: "; getline(cin, cname);

                        if (!usernameToID.count(cname)) {
                            cout << "Error: User not found!\n";
                            continue;
                        }
                        int senderID = usernameToID[cname];

                        if (!me->isContactID(senderID)) {
                            cout << "Error: " << cname << " is not in your contact list. Use Option 10 to see all received messages.\n";
                            continue;
                        }

                        me->viewReceivedFrom(senderID, users);
                    }
                    else if (ch == 7) me->addFavorite();
                    else if (ch == 8) me->removeOldestFavorite();
                    else if (ch == 9) me->viewFavorites();
                    else if (ch == 10) me->viewAllReceived(users);
                    else {
                        cout << "Invalid choice.\n";
                    }
                }
            }
            else {
                cout << "Invalid choice.\n";
            }
        }
    }
};

// ================= Main =================
int main() {
    App app;
    app.run();
    return 0;
}