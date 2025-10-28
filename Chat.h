#pragma once
#include <iostream>
#include <string>
#include "User.h"

using namespace  std;

class Chat
{
private:
    User users[MAX_USERS];
    int usersCount = 0;
    User* loggedInUser = nullptr;

    User* findUserByLogin(const string& login) {
        for (int i = 0; i < usersCount; i++) {
            if (users[i].getLogin() == login) {
                return &users[i];
            }
        }
        return nullptr;
    }
public:
    void registerUser();
    void login();
    void logout();
    void sendMessage();
    void checkMessages();

    void run(); 

};

