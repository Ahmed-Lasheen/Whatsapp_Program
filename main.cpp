#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip> 
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <memory>

using namespace std;

// ========================
//       USER CLASS
// ========================
class User {
private:
    string username;
    string password;
    string phoneNumber;
    string status;
    string lastSeen;
    vector<string> blockedUsers;

    string getCurrentTime(){
        time_t now = time(0);
        tm *ltm = localtime(&now);

        ostringstream oss;
        oss << 1900 + ltm->tm_year << "-"
            << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
            << setw(2) << setfill('0') << ltm->tm_mday << " "
            << setw(2) << setfill('0') << ltm->tm_hour << ":"
            << setw(2) << setfill('0') << ltm->tm_min << ":"
            << setw(2) << setfill('0') << ltm->tm_sec;

        return oss.str();
    }

public:
    User() {
        // TODO: Implement default constructor
        username = "Unknown";
        password = "";
        phoneNumber = "";
        status = "Offline";
        lastSeen = getCurrentTime();
    }

    User(string uname, string pwd, string phone) {
        // TODO: Implement parameterized constructor
        username = uname;
        password = pwd;
        phoneNumber = phone;
        status = "Offline";
        lastSeen = getCurrentTime();

    }
    string getUsername() const {
        // TODO: Implement getter
        return username;

    }
    string getPassword() {
        return password;
    }

    string getPhoneNumber() const {
        // TODO: Implement getter
        return phoneNumber;
    }

    string getStatus() const {
        // TODO: Implement getter
        return status;
    }

    string getLastSeen() const {
        // TODO: Implement getter
        return lastSeen;
    }

    void setStatus(string newStatus) {
        // TODO: Implement setter
        if(newStatus == "Online" || newStatus == "Offline") {
            status = newStatus;
            if(newStatus == "Online") {
                updateLastSeen();
            }
        }
    }

    void setPhoneNumber(string phone) {
        // TODO: Implement setter
        phoneNumber = phone;
    }

    void updateLastSeen() {
        // TODO: Implement last seen update
        time_t now = time(nullptr);
        tm tm_now;
#ifdef _WIN32
        localtime_s(&tm_now, &now);
#else
        localtime_r(&now, &tm_now);
#endif
        char buf[64];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm_now);
        lastSeen = string(buf);
    }

    bool checkPassword(string pwd) const {
        // TODO: Implement password check
        if(password == pwd){
          return true;
        }
         else{
             return false;
         }

    }

    void changePassword(string newPwd) {
        // TODO: Implement password change
        password = newPwd;
    }

    void blockUser(const string& other){
        if (find(blockedUsers.begin(), blockedUsers.end(), other) == blockedUsers.end())
            blockedUsers.push_back(other);
    }
    void unblockUser(const string& other) {
        blockedUsers.erase(remove(blockedUsers.begin(), blockedUsers.end(), other), blockedUsers.end());
    }
    bool isBlocked(const string& other) const {
        return find(blockedUsers.begin(), blockedUsers.end(), other) != blockedUsers.end();
    }
};

// ========================
//      MESSAGE CLASS
// ========================
class Message {
private:
    string sender;
    string content;
    string timestamp;
    string status;
    string replySender;
    string replySnippet;
    bool edited;

public:
    Message() : sender("Unknown"), content(""), status("sent"),
                replySender(""), replySnippet(""), edited(false) {
        updateTimestamp();
    }

    Message(string sndr, string cntnt) : sender(sndr), content(cntnt), status("sent"),
                replySender(""), replySnippet(""), edited(false) {
        updateTimestamp();
    }
    string getContent() const {
        // TODO: Implement getter
        return content;
    }

    string getSender() const {
        // TODO: Implement getter
        return sender;
    }

    string getTimestamp() const {
        // TODO: Implement getter
        return timestamp;
    }

    string getStatus() const {
        // TODO: Implement getter
        return status;
    }

    bool isEdited() const {
         return edited; 
    }

    string getReplySender() const { 
        return replySender; 
    }
    string getReplySnippet() const {
        return replySnippet; 
    }

    void setStatus(string newStatus) {
        // TODO: Implement setter
        status= newStatus;
    }

    void setReply(const string& origSender, const string& origSnippet) {
        replySender = origSender;
        replySnippet = origSnippet;
    }

    void editContent(const string& newContent){
        content = newContent;
        edited = true;
        updateTimestamp();
    }
    void updateTimestamp() {
        // TODO: Implement timestamp update
         time_t now = time(nullptr);
        tm tm_now;
#ifdef _WIN32
        localtime_s(&tm_now, &now);
#else
        localtime_r(&now, &tm_now);
#endif
        char buf[64];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm_now);
        timestamp = string(buf);
    }

    void display() const {
        if (status == "deleted") {
            cout << "[deleted message]\n";
            return;
        }
        if (!replySender.empty()) {
            cout << "(reply to " << replySender << ": \"" << replySnippet << "\")\n";
        }
        cout << timestamp << " | " << sender << ": \"" << content << "\"";
        if (edited) cout << " (edited)";
        cout << " | " << status << "\n";
    }

    void addEmoji(string emojiCode) {
        // TODO: Implement emoji support
        content += emojiCode;
        updateTimestamp();
    }
};

// ========================
//       CHAT CLASS (BASE)
// ========================
class Chat {
protected:
    vector<string> participants;
    vector<Message> messages;
    string chatName;
    vector<string> mutedByUsers;

public:
    Chat() {
        // TODO: Implement default constructor
        chatName="N/A";
    }



    Chat(vector<string> users, string name) {
        for (string user : users)
        {
            participants.push_back(user);
        }
        chatName=name;
    }

    virtual ~Chat() = default;

    string getChatName()
    {
        return chatName;
    }
    bool isMutedBy(const string& username)const{
        return find(mutedByUsers.begin(), mutedByUsers.end(), username) != mutedByUsers.end();
    }

    void muteForUser(const string& username) {
        if (!isMutedBy(username)) mutedByUsers.push_back(username);
    }
    void unmuteForUser(const string& username) {
        mutedByUsers.erase(remove(mutedByUsers.begin(), mutedByUsers.end(), username), mutedByUsers.end());
    }

    void addMessage(const Message& msg) {
        messages.push_back(msg);
        if (!messages.empty()) messages.back().setStatus("delivered");
    }

    bool deleteMessage(int index, const string& username) {
        if (index < 0 || index >= (int)messages.size()) {
            cout << "THAT'S NOT A VALID INDEX!! please enter index between (0," << messages.size()-1 << ")\n";
            return false;
        }
        
        Message &m = messages[index];
        if (m.getSender() != username) {
            cout << "You can only delete your own messages (for now).\n";
            return false;
        }
        m.editContent(username + " has deleted this message");
        m.setStatus("deleted");
        return true;
    }

    virtual void displayChatFor(const string& viewer){
        for(size_t i = 0; i < messages.size(); ++i){
            if(messages[i].getStatus() == "delivered") messages[i].setStatus("read");
            cout << i << " - ";
            messages[i].display();
        }
    }

    vector<Message> searchMessages(const string& keyword) const{
        vector<Message> found;
        if(keyword.empty()) return found;
        for(const Message& m : messages){
            if(m.getContent().find(keyword) != string::npos) found.push_back(m);
        }
        return found;
    }

    void exportToFile(const string& filename) const {
        ofstream outfile(filename.c_str());
        if(!outfile){
            cout << "Error Couldn't export to the desired file\n";
            return;
        }
        outfile << "Chat: " << chatName << "\n\n";
        for(size_t i = 0 ; i < messages.size(); ++i){
            outfile << i <<" - "<<messages[i].getTimestamp()<<" | "
                    << messages[i].getSender()<<" : "<<messages[i].getContent()
                    <<" | "<<messages[i].getStatus()<< "\n";
        }
        outfile.close();
    }
    
    bool isParticipant(const string& username) const{
        return find(participants.begin(), participants.end(), username) != participants.end();
    }

    void showParticipants() const{
        cout << "Participants in \"" << chatName << "\":\n";
        for (const auto &p: participants) cout << " - " << p << "\n";
    }

    const vector<Message>& getMessagesRef() const { return messages; }
    vector<Message>& getMessagesRefNonConst() { return messages; }
};

// ========================
//     PRIVATE CHAT CLASS
// ========================
class PrivateChat : public Chat {
private:
    string user1;
    string user2;

public:
    PrivateChat(string u1, string u2){
        // TODO: Implement constructor
        user1=u1;
        user2=u2;
        chatName=u1+" & "+u2;
        participants.push_back(user1);
        participants.push_back(user2);
    }

    void displayChatFor(const string& username)  override {
        // TODO: Implement private chat display
        Chat::displayChatFor(username);
    }

    void showTypingIndicator(const string& username) const {
        // TODO: Implement typing indicator
        cout<<username<<" is Typing..."<<endl;
    }
};

// ========================
//      GROUP CHAT CLASS
// ========================
class GroupChat : public Chat {
private:
    vector<string> admins;
    string description;

public:
    GroupChat(const vector<string>& users, const string& name, const string& creator)
        : Chat(users, name) {
        admins.push_back(creator);
        description = "No description";
        chatName = name;
    }

    void addAdmin(const string& newAdmin) {
        if (find(admins.begin(), admins.end(), newAdmin) == admins.end())
            admins.push_back(newAdmin);
    }

    bool removeParticipant(const string& admin, const string& userToRemove) {
        if(!isAdmin(admin)) return false;
        for(vector<string>::iterator it = participants.begin(); it != participants.end(); ++it){
            if(*it == userToRemove){
                participants.erase(it);
                return true;
            }
        }
        return false;
    }

    bool isAdmin(string username) const {
        for(size_t i = 0; i < admins.size();i++){
            if(admins[i] == username){
                return true;
            }
        }
        return false;
    }

    bool isParticipant(string username) const {
        for(size_t i = 0; i < participants.size(); i++){
            if(participants[i] == username){
                return true;
            }
        }
        return false;
    }

    void setDescription(const string& desc) { description = desc; }

    void displayChatFor(const string& viewer) override {
        cout << "== Group: " << chatName << " ==\nDescription: " << description << "\n";
        Chat::displayChatFor(viewer);
    }

    void sendJoinRequest(const string& username) {
        cout << username << " has requested to join the group " << chatName << "\n";
    }
};

// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp {
private:
    vector<User> users;
    vector<Chat*> chats;
    int currentUserIndex;

    int findUserIndex(const string& username) const {
        for (size_t i = 0; i < users.size(); i++){
            if(users[i].getUsername() == username) return i;
        }
        return -1;
    }

    bool isLoggedIn() const {
        return currentUserIndex != -1;
    }

    string getCurrentUsername() const { 
        if (!isLoggedIn()) return "";
        return users[static_cast<size_t>(currentUserIndex)].getUsername(); 
    }

    string formatTimeNow() const {
        time_t now = time(nullptr);
        tm tm_now;
#ifdef _WIN32
        localtime_s(&tm_now, &now);
#else
        localtime_r(&now, &tm_now);
#endif
        char buf[64];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm_now);
        return string(buf);
    }

    void loadUsers(){
        ifstream file("users.txt");
        if(!file) return;
        string line;
        while(getline(file, line)){
            if(line.empty()) continue;
            stringstream ss(line);
            string username, pass, phone, status, lastSeen;
            getline(ss, username, '|');
            getline(ss, pass, '|');
            getline(ss, phone, '|');
            getline(ss, status, '|');
            getline(ss, lastSeen, '|');

            User u(username, pass, phone);
            if(status == "Online" || status == "Offline") u.setStatus(status);
            users.push_back(u);
        }
    }

    void saveUsers(const string &filename = "users.txt") {
    ofstream out(filename.c_str());
    if (!out) {
        cerr << "Error: Could not open file for saving users.\n";
        return;
    }

    for (size_t i = 0; i < users.size(); ++i) {
        out << users[i].getUsername() << "|"
            << users[i].getPassword() << "|"
            << users[i].getPhoneNumber() << "|"
            << users[i].getStatus() << "|"
            << users[i].getLastSeen() << "\n";
    }
}


public:
    WhatsApp() : currentUserIndex(-1) {
        loadUsers();
    }

    ~WhatsApp(){
        for(Chat* chat : chats){
            delete chat;
        }
        saveUsers();
    }

    void signUp() {
        string uname, pwd, phone;
        cout <<"Enter username: ";
        cin>> uname;
        if(findUserIndex(uname)!= -1){
            cout << "User already exists.\n";
            return;
        }
        cout << "Enter password: ";
        cin >> pwd;

        cout << "Enter phone Number: ";
        cin >> phone;

        users.push_back(User(uname, pwd, phone));
        saveUsers();
        cout << "Account created successfully!\n";
    }

    void login() {
        string uname, pwd;
        cout << "Enter username: ";
        cin >> uname;

        cout << "Enter password: ";
        cin >> pwd;

        int idx = findUserIndex(uname);
        if(idx != -1 && users[static_cast<size_t>(idx)].checkPassword(pwd)){
            currentUserIndex = idx;
            users[static_cast<size_t>(idx)].updateLastSeen();
            users[static_cast<size_t>(idx)].setStatus("Online");
            cout << "Login successful. \n";
        } else{
            cout << "Invalid usrname or password.\n";
        }
    }

    void logout(){
        if(isLoggedIn()){
             users[static_cast<size_t>(currentUserIndex)].setStatus("Offline");
            users[static_cast<size_t>(currentUserIndex)].updateLastSeen();
        }
        currentUserIndex = -1;
        cout << "Logged out successfully. \n";
    }

    void startPrivateChat() {
       if (!isLoggedIn()) { cout << "Please login first.\n"; return; }
        string other;
        cout << "Enter username to chat with: ";
        cin >> other;
        if (findUserIndex(other) == -1) {
            cout << "User not found.\n";
            return;
        }
        chats.push_back(new PrivateChat(getCurrentUsername(), other));
        cout << "Private chat started with " << other << "...\n";
    }

    void createGroup() {
       if (!isLoggedIn()) { cout << "Please login first.\n"; return; }
        string name;
        vector<string> members;
        int cnt;
        cout << "Enter group name: ";
        cin.ignore (numeric_limits<streamsize>::max(), '\n'); 
        getline(cin, name);
        cout << "Enter participants count other than you: ";
        cin>>cnt;
        cin.ignore (numeric_limits<streamsize>::max(), '\n'); 
        for(int i=0;i<cnt;i++)
        {
            string memb;
            cout << "Enter a participant name: ";
            getline(cin,memb);
            members.push_back(memb);    
        }
        members.push_back(getCurrentUsername());
        chats.push_back(new GroupChat(members, name, getCurrentUsername()));
        cout << "Group created successfully.\n";
    }

    void viewChats() {
        string me = getCurrentUsername();
        for (int i = 0; i < chats.size(); i++) {
            if (chats[i]->isParticipant(me)) {  
                cout << i << " - " << chats[i]->getChatName()
                    << " (messages: " << chats[i]->getMessagesRef().size() << ")\n";
            }
    }
}

    void accessChat() {
        if (!isLoggedIn()) { cout << "Please login first.\n"; return; }
        while (true) {
            viewChats();
            cout << "1. choose a chat by index  |  2. go back to main menu\nChoice: ";
            int choice;
            cin >> choice;
            if (choice == 2) return;
            if (choice == 1) {
                int idx;
                cout << "Enter the index: ";
                cin >> idx;
                if (idx < 0 || static_cast<size_t>(idx) >= chats.size()) { cout << "Invalid index.\n"; continue; }
                editChats(idx);
            } else {
                cout << "that's not a valid option\n";
            }
        }
    }

     void editChats(int idx) {
        if (!isLoggedIn()) return;
        Chat* chat = chats[idx];
        GroupChat* gchat=dynamic_cast<GroupChat*>(chat);
        while (true) {
            cout << "\n--- Chat: " << chat->getChatName() << " ---\n";
            chat->displayChatFor(getCurrentUsername());
            cout << "\nwhat do you want to do ?\n";
            
            cout << "1. Send message\n2. Delete message\n3. Search messages\n4. Export chat to txt file\n5. Reply to a message\n6. Edit one of your messages\n7. Forward a message to another chat\n8. Show participants\n9. Mute/Unmute chat\n10. Go back\n";
            if (gchat) {
                    cout << "----groupchat options----\n11. Remove participant\n"
                         << "12. set group description\nChoice:";
                }
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice == 1) {
                string msg;
                cout << "Enter the message you want to send: ";
                getline(cin, msg);
                string me = getCurrentUsername();
                if (!chat->isParticipant(me)) {
                    cout << "You are not a participant of this chat.\n";
                    continue;
                }
                Message m(me, msg);
                chat->addMessage(m);
            }
            else if (choice == 2) {
                cout << "Which message do you want to delete by index: ";
                int del;
                cin >> del;
                chat->deleteMessage(del, getCurrentUsername());
            }
            else if (choice == 3) {
                string keyword;
                cout << "Enter the keyword you want: ";
                getline(cin, keyword);
                vector<Message> found = chat->searchMessages(keyword);
                for (size_t i = 0; i < found.size(); i++) {
                    cout << "FOUND: " << found[i].getSender() << ": \"" << found[i].getContent()
                         << "\" | " << found[i].getTimestamp() << "\n";
                }
            }
            else if (choice == 4) {
                string filename;
                cout << "Enter the file name you want without extension: ";
                getline(cin, filename);
                chat->exportToFile(filename + ".txt");
                cout << "Exported.\n";
            }
            else if (choice == 5) { //replay
                cout << "Which message index do you want to reply to? ";
                int ridx;
                cin >> ridx;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (ridx < 0 || ridx >= (int)chat->getMessagesRef().size()) {
                    cout << "Invalid index.\n";
                    continue;
                }
                const Message& orig = chat->getMessagesRef()[static_cast<size_t>(ridx)];
                cout << "Enter your reply: ";
                string reply;
                getline(cin, reply);
                Message m(getCurrentUsername(), reply);
                string snippet = orig.getContent().substr(0, min((size_t)30, orig.getContent().size()));
                m.setReply(orig.getSender(), snippet);
                chat->addMessage(m);
            }
            else if (choice == 6) { // edit
                cout << "Which of your message indices do you want to edit? ";
                int midx;
                cin >> midx;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (midx < 0 || midx >= (int)chat->getMessagesRefNonConst().size()) {
                    cout << "Invalid index.\n";
                    continue;
                }
                Message &mref = chat->getMessagesRefNonConst()[static_cast<size_t>(midx)];
                if (mref.getSender() != getCurrentUsername()) {
                    cout << "You can only edit your own messages.\n";
                    continue;
                }
                cout << "Enter new content: ";
                string newc;
                getline(cin, newc);
                mref.editContent(newc);
            }
            else if (choice == 7) { // forward
                cout << "Which message index do you want to forward? ";
                int fidx;
                cin >> fidx;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (fidx < 0 || fidx >= (int)chat->getMessagesRef().size()) {
                    cout << "Invalid index.\n";
                    continue;
                }
                cout << "Forward to which chat index? ";
                int targetIdx;
                viewChats();
                cin >> targetIdx;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (targetIdx < 0 || targetIdx >= (int)chats.size()) {
                    cout << "Invalid chat index.\n";
                    continue;
                }
                const Message& orig = chat->getMessagesRef()[static_cast<size_t>(fidx)];
                Message forwarded(getCurrentUsername(), string("Forwarded: ") + orig.getContent());
                chats[static_cast<size_t>(targetIdx)]->addMessage(forwarded);
                cout << "Message forwarded.\n";
            }
            else if (choice == 8) {
                chat->showParticipants();
            }
            else if (choice == 9) {
                string me = getCurrentUsername();
                if (!chat->isMutedBy(me)) {
                    chat->muteForUser(me);
                    cout << "Muted this chat for you.\n";
                } else {
                    chat->unmuteForUser(me);
                    cout << "Unmuted this chat for you.\n";
                }
            }
            else if (choice == 10) {
                return;
            } 
            else if (choice == 11 && gchat) { // remove participant
                string username;
                cout << "Enter username to remove: ";
                getline(cin, username);
                gchat->removeParticipant(getCurrentUsername(),username);
            }
            else if (choice == 12 && gchat) { // set description
                string description;
                cout << "Enter group description: ";
                getline(cin, description);
                gchat->setDescription(description);
            }
            else {
                cout << "Invalid choice.\n";
            }
        }
    }

    void run() {
        while (true) {
            if (!isLoggedIn()) {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1) login();
                else if (choice == 2) signUp();
                else if (choice == 3) break;
            }
            else {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Access a Chat \n5. Logout\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1) startPrivateChat();
                else if (choice == 2) createGroup();
                else if (choice == 3) viewChats();
                else if (choice == 4) accessChat();
                else if (choice == 5) logout();
            }
        }
    }
};

// ========================
//          MAIN
// ========================
int main() {
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}
