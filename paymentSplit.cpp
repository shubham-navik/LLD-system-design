#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// User class
class User {
public:
    string userId;
    string name;
    string email;
    string phone;
    vector<User*> friends;  // List of friends

    User(string id, string n, string e, string p) : userId(id), name(n), email(e), phone(p) {}

    // Add a friend to the user
    void addFriend(User* friendUser) {
        friends.push_back(friendUser);
    }
};


// SplitwiseApp class
class SplitwiseApp {
private:
    unordered_map<string, User*> users;
    unordered_map<string, double> balances;

    void splitEqual(User* paidBy, double amount, vector<User*> involvedUsers) {
        double splitAmount = amount / involvedUsers.size();
        for (User* user : involvedUsers) {
            if (user->userId == paidBy->userId) continue;
            balances[user->userId] -= splitAmount;
            balances[paidBy->userId] += splitAmount;
        }
    }

    void splitExact(User* paidBy, vector<User *> involvedUsers, vector<double> amounts) {
        for (size_t i = 0; i < involvedUsers.size(); i++) {
            if (involvedUsers[i]->userId == paidBy->userId) continue;
            balances[involvedUsers[i]->userId] -= amounts[i];
            balances[paidBy->userId] += amounts[i];
        }
    }

    void splitPercent(User*  paidBy, double amount, vector<User* > involvedUsers, vector<double> percents) {
        for (size_t i = 0; i < involvedUsers.size(); i++) {
            double splitAmount = (amount * percents[i]) / 100.0;
            if (involvedUsers[i]->userId == paidBy->userId) continue;
            balances[involvedUsers[i]->userId] -= splitAmount;
            balances[paidBy->userId] += splitAmount;
        }
    }

public:
    // Add a user to the SplitwiseApp
    void addUser(User* user) {
        users[user->userId] = user;

        // User* newUser = new User(userId, name, email, phone);
        // users[userId] = newUser;
        balances[user->userId] = 0.0; // Initialize balance as 0 for every new user
        cout << "User " << user->name << " added." << endl;
    }

    // Add an expense
    void addExpense(User* paidBy, double amount, vector<User*> involvedUsers, string splitType, vector<double> values) {
        if (splitType == "EQUAL") {
            splitEqual(paidBy, amount, involvedUsers);
        } else if (splitType == "EXACT") {
            splitExact(paidBy, involvedUsers, values);
        } else if (splitType == "PERCENT") {
            splitPercent(paidBy, amount, involvedUsers, values);
        }
        cout << "Expense added: " << amount << " paid by " << users[paidBy->userId]->name << endl;
    }

    // Show all balances
    void showBalances() {
        bool noBalances = true;
        for (auto& balance : balances) {
            if (balance.second != 0) {
                cout << users[balance.first]->name << " owes " << balance.second << endl;
                noBalances = false;
            }
        }
        if (noBalances) {
            cout << "No balances" << endl;
        }
    }

    // Show balance for a specific user
    void showUserBalance(User* user) {
        if(balances.find(user->userId)==balances.end()){
            cout << "user " << user->name << " not exist" << endl;
            return;
        }
        double balance = balances[user->userId];
        if (balance == 0) {
            cout << users[user->userId]->name << " has no balance" << endl;
        } else if (balance < 0) {
            cout << users[user->userId]->name << " owes " << -balance << endl;
        } else {
            cout << users[user->userId]->name << " is owed " << balance << endl;
        }
    }

    void showAllUsers(){
        for(auto user:users){
            cout << "userId : " << user.first << endl;
        }
    }

    void showFriendOfUser(string userId){
        if(users.find(userId)!=users.end()){
            User* friends = users[userId];
            cout << "Friend of " << userId << " : ";
            for(auto frinds : friends->friends){
                cout << frinds->name << " ";
            }
            cout << endl;
        }else{
            cout << "user " << userId << " not found\n";
        }
    }
};

int main() {
    SplitwiseApp app;

    // Adding some users to the application
    // app.addUser("u1", "User1", "user1@mail.com", "9999999999");
    // app.addUser("u2", "User2", "user2@mail.com", "8888888888");
    // app.addUser("u3", "User3", "user3@mail.com", "7777777777");
    // app.addUser("u4", "User4", "user4@mail.com", "6666666666");

    // // Sample input processing
    // app.addExpense("u1", 1000, {"u1", "u2", "u3", "u4"}, "EQUAL", {});
    // app.showBalances();

    // app.addExpense("u1", 1250, {"u2", "u3"}, "EXACT", {370, 880});
    // app.showBalances();

    // app.addExpense("u4", 1200, {"u1", "u2", "u3", "u4"}, "PERCENT", {40, 20, 20, 20});
    // app.showUserBalance("u1");
    // app.showBalances();
    app.showBalances();

    User *u1 = new User("u1", "User1", "user1@mail.com", "1777777777");
    User *u2 = new User("u2", "User2", "user2@mail.com", "2777777777");
    User *u3 = new User("u3", "User3", "user3@mail.com", "3777777777");
    User *u4 = new User("u4", "User4", "user4@mail.com", "4777777777");
    // app.showUserBalance("u1");
    app.addUser(u1);
    app.addUser(u2);
    app.addUser(u3);
    app.addUser(u4);
    // app.showAllUsers();
    // app.showFriendOfUser("u1");
     app.addExpense(u1, 100, {u1,u2,u3}, "EQUAL", {});
     app.showUserBalance(u1);
     app.showUserBalance(u2);
     app.showUserBalance(u3);
     app.showAllUsers();

     return 0;
}
