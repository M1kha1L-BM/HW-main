#include "User.h"


User::User(const string& login, const string& password, const string& name)
    : login(login), password(password), name(name), inboxCount(0) {
}

bool User:: addMessage(const string& msg) {
    if (inboxCount >= MAX_MESSAGES) {
        // ���  ������������, ����� �� ��������� ��� �������� ������
        return false;
    }
    inbox[inboxCount++] = msg;
    return true;
}

string User::getLogin() const { return login; }
string User::getPassword() const { return password; }
string User::getName() const { return name; }

void  User::showInbox() {
    if (inboxCount == 0) {
        cout << "��� ����� ���������" << endl;
        return;
    }
    cout << "--- ��������� ��� " << name << endl;
    for (int i = 0; i < inboxCount; i++) {
        cout << inbox[i] << endl;
    }
    inboxCount = 0;
}

