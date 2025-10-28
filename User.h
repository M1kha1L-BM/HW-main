#pragma once
#include <iostream>
#include <string>

using namespace std;

const int MAX_USERS = 100;
const int MAX_MESSAGES = 100;

class User
{
private:
    string login;
    string password;
    string name;

    string inbox[MAX_MESSAGES];
    int inboxCount = 0;

public:
    User() {}
    User(const string& login, const string& password, const string& name);

    string getLogin() const;
    string getPassword()  const;
    string getName() const;

    bool addMessage(const string& msg); 
    void showInbox();

};

