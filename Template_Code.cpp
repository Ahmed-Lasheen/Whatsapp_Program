#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
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
    
public:
    User() {
        // TODO: Implement default constructor
    }
    
    User(string uname, string pwd, string phone) {
        // TODO: Implement parameterized constructor
    }
    
    string getUsername() const {
        // TODO: Implement getter
        return "";
    }
    
    string getPhoneNumber() const {
        // TODO: Implement getter
        return "";
    }
    
    string getStatus() const {
        // TODO: Implement getter
        return "";
    }
    
    string getLastSeen() const {
        // TODO: Implement getter
        return "";
    }
    
    void setStatus(string newStatus) {
        // TODO: Implement setter
    }
    
    void setPhoneNumber(string phone) {
        // TODO: Implement setter
    }
    
    void updateLastSeen() {
        // TODO: Implement last seen update
    }
    
    bool checkPassword(string pwd) const {
        // TODO: Implement password check
        return false;
    }
    
    void changePassword(string newPwd) {
        // TODO: Implement password change
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
    Message* replyTo;
    
public:
    Message() {
        // TODO: Implement default constructor
    }
    
    Message(string sndr, string cntnt) {
        // TODO: Implement parameterized constructor
    }
    
    string getContent() const {
        // TODO: Implement getter
        return "";
    }
    
    string getSender() const {
        // TODO: Implement getter
        return "";
    }
    
    string getTimestamp() const {
        // TODO: Implement getter
        return "";
    }
    
    string getStatus() const {
        // TODO: Implement getter
        return "";
    }
    
    Message* getReplyTo() const {
        // TODO: Implement getter
        return nullptr;
    }
    
    void setStatus(string newStatus) {
        // TODO: Implement setter
    }
    
    void setReplyTo(Message* msg) {
        // TODO: Implement setter
    }
    
    void updateTimestamp() {
        // TODO: Implement timestamp update
    }
    
    void display() const {
        // TODO: Implement message display
    }
    
    void addEmoji(string emojiCode) {
        // TODO: Implement emoji support
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
    
public:
    bool keywordCompare(string keyword , string current_message)
    {
        int textLen = current_message.length();
        int keyLen = keyword.length();
        for (int i = 0; i <= textLen - keyLen; i++) 
        {
            bool found =1;
            for (int j = 0; j < keyLen; j++) 
            {
                if (current_message[i + j] != keyword[j])
                {
                    found = 0;
                    break;
                }
            }
            if(found)
             return found;
        }
        return 0;
    }
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
    
    void addMessage(const Message& msg) {
        messages.push_back(msg);
    }
    
    bool deleteMessage(int index, const string& username) {
        if(index<=messages.size()||index>0)
        {
        for(int i=0 ; i<messages.size() ; i++)
        {
            if(i==index-1)
            {
                cout << "-"<<username <<" deleted this message "<<messages[i].getContent()<<endl;
                return true;
            }
        }
        return false;
        }
        else 
            cout<<"THAT'S NOT A VALID INDEX!! please enter index between ("<<1<<","<<messages.size()<<endl;
    }
    
    virtual void displayChat() const {
        for(int i=0 ; i<messages.size() ; i++)
        {
           if(messages[i].getStatus()!="read")
                messages[i].setStatus("read")=;

           cout << "-"<<messages[i].getSender()<<" : "<<messages[i].getContent()<<endl;
        }
    }
    
    vector<Message> searchMessages(string keyword) const {
        vector<Message> found;
        for(int i=0 ;  i<messages.size() ;  i++)
        {
            if(keywordCompare(keyword,messages[i].getContent()))
            {
                found.push_back(messages[i]);
            }
        }
        return found;
    }
    
    void exportToFile(const string& filename) const 
    {
        // TODO: Implement export to file
        ofstream outfile;
        outfile.open(filename);
        if(outfile.is_open())
        {
            outfile <<"chat : "<< chatName <<endl<<endl;
            for(Message m : messages)
            {
                outfile <<" - " <<m.getSender<<" : \""<<m.getContent<<"\""<<endl;
            }
            outfile.close();
        }
        else 
        cout<<"ERROR COULD NOT EXPORT TO THE DESIRED FILE"<<endl;
    }
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
        participants.push_back(user1);
        participants.push_back(user2);
    }
    
    void displayChat() const override {
        // TODO: Implement private chat display
        for(int i=0 ; i<messages.size() ; i++)
        {
            if(messages[i].getStatus()!="read")
                messages[i].setStatus("read");

           cout << "-"<<messages[i].getSender()<<" : "<<messages[i].getContent()<<endl;
        }
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
    GroupChat(vector<string> users, string name, string creator) : Chat(users, name){
        admins.push_back(creator);
        description = "No description";
    }
    
    void addAdmin(string newAdmin) {
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
        for(int i = 0; i < (int)admins.size();i++){
            if(admins[i] == username){
                return true;
            }
        }
        return false;
    }
    
    bool isParticipant(string username) const {
        for(int i = 0; i < (int)participants.size(); i++){
            if(participants[i] == username){
                return true;
            }
        }
        return false;
    }        
    
    void setDescription(string desc) {
        description = desc;
    }
    
    void displayChat() const override {
        cout << "== Group: " << chatName << " ===\nDescription: " << description << "\n";
        for (vector<Message>::const_iterator it = messages.begin(); it != messages.end(); ++it){
            it->display();
        }
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
    
    int findUserIndex(string username) const {
        for (int i = 0; i < (int)users.size(); i++){
            if(users[i].getUsername() == username) return i;
        }
        return -1;
    }
    
    bool isLoggedIn() const {
        return currentUserIndex != -1;
    }
    
    string getCurrentUsername() const {
        return users[currentUserIndex].getUsername();
    }

    void loadUsers(){
        ifstream file("users.txt");
        string line;
        while(getline(file, line)){
            stringstream ss(line);
            string username, pass, phone, status;
            getline(ss, username, '|');
            getline(ss, pass, '|');
            getline(ss, phone, '|');
            getline(ss, status);

            User u(username, pass, phone);
            u.setStatus(status);
            users.push_back(u);
        }
    }

    void saveUsers(const string &filename = "users.txt") {
    ofstream out(filename.c_str());
    if (!out) {
        cerr << "Error: Could not open file for saving users.\n";
        return;
    }

    for (int i = 0; i < (int)users.size(); ++i) {
        out << users[i].getUsername() << "|"
            << users[i].getPassword() << "|"
            << users[i].getPhoneNumber() << "|"
            << users[i].getStatus() << "|"
            << users[i].getLastSeen()
            << endl;
    }
}

    
public:
    WhatsApp() : currentUserIndex(-1) {
        loadUsers();
    }

    ~WhatsApp(){
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
        saveUsers("users.txt");
        cout << "Account created successfully!\n";
    }
    
    void login() {
        string uname, pwd;
        cout << "Enter username: ";
        cin >> uname;

        cout << "Enter password: ";
        cin >> pwd;

        int idx = findUserIndex(uname);
        if(idx != -1 && users[idx].checkPassword(pwd)){
            currentUserIndex = idx;
            users[idx].updateLastSeen();
            cout << "Login successful. \n";
        } else{
            cout << "Invalid usrname or password.\n";
        }
    }
    
    void startPrivateChat() {
        string other;
        cout << "Enter username to chat with : ";
        cin >> other;
        if(findUserIndex(other) == -1){
            cout << "User not found.\n";
            return;
        }
        chats.push_back(new PrivateChat(getCurrentUsername(), other));
        cout << "Private chat started with " << other << "...\n";
    }
    
    void createGroup() {
        string name;
        cout << "Enter group name: ";
        cin >> name;
        vector<string>members;
        members.push_back(getCurrentUsername());
        chats.push_back(new GroupChat(members, name, getCurrentUsername()));
        cout << "Group created successfully. \n";
    }
    
    void viewChats() const {
        for (vector<Chat*>::const_iterator it = chats.begin(); it != chats.end(); ++it){
            (*it)->displayChat();
        }
    }
    
    void logout() {
        currentUserIndex = -1;
        cout << "logged out succssfully. \n";
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
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";
                int choice;
                cin >> choice;
                
                if (choice == 1) startPrivateChat();
                else if (choice == 2) createGroup();
                else if (choice == 3) viewChats();
                else if (choice == 4) logout();
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