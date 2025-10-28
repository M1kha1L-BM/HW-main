#include "Chat.h"

void Chat:: registerUser() {
    if (usersCount >= MAX_USERS) {
        cout << "Превышен лимит пользователей"<<endl;
        return;
    }

    cout << "Регистрация нового пользователя" << endl;
    string login, password, name;
    cout << "Введите логин: ";
    cin >> login;

    if (findUserByLogin(login) != nullptr) {
        cout << "Такой логин уже существует" << endl;
        return;
    }

    cout << "Введите пароль: " << endl;
    cin >> password;
    cout << "Введите имя: " << endl;
    cin.ignore();
    getline(cin, name);

    users[usersCount++] = User(login, password, name);
    cout << "Пользователь зарегистрирован" << endl;
}

void  Chat:: login() {
    cout << "Вход в систему" << endl;
    string login, password;
    cout << "Логин: " << endl;
    cin >> login;
    cout << "Пароль: " << endl;
    cin >> password;

    User* user = findUserByLogin(login);
    if (user != nullptr && user->getPassword() == password) {
        loggedInUser = user;
        cout << "Добро пожаловать, " << loggedInUser->getName() << "! " << endl;
    }
    else {
        cout << "Введен неверный логин или пароль." << endl;
    }
}

void Chat:: logout() {
    if (loggedInUser) {
        cout << "Пользователь " << loggedInUser->getName() << " вышел из чата" << endl;
        loggedInUser = nullptr;
    }
    else {
        cout << "Вы не вошли в систему" << endl;
    }
}

void  Chat:: sendMessage() {
    if (!loggedInUser) {
        cout << "Сначала войдите в систему " << endl;
        return;
    }

    cout << "Введите логин получателя (или 'all' для сообщения всем): " << endl;
    string to;
    cin >> to;
    cout << "Введите сообщение: " << endl;
    cin.ignore();
    string text;
    getline(cin, text);

    if (to == "all") {
        int sentCount = 0;
        for (int i = 0; i < usersCount; i++) {
            if (users[i].getLogin() != loggedInUser->getLogin()) {
                if (users[i].addMessage("[Общий чат] " + loggedInUser->getName() + ": " + text)) {
                    sentCount++;
                }
            }
        }
        cout << "Сообщение отправлено " << sentCount << " пользователям " << endl;
    }
    else {
        User* user = findUserByLogin(to);
        if (user != nullptr) {
            if (user->addMessage("[Личное] " + loggedInUser->getName() + ": " + text)) {
                cout << "Сообщение отправлено пользователю " << user->getName() << endl;
            }
            else {
                cout << "Почтовый ящик пользователя переполнен. Сообщение не доставлено" << endl;
            }
        }
        else {
            cout << "Пользователь с таким логином не найден " << endl;
        }
    }
}

void  Chat:: checkMessages() {
    if (!loggedInUser) {
        cout << "Сначала войдите в систему" << endl;
        return;
    }
    loggedInUser->showInbox();
}

void Chat:: run() {
    while (true) {
        cout << "\n--- Меню ---\n";
        cout << "1. Регистрация" << endl;
        cout << "2. Вход" << endl;
        cout << "3. Отправить сообщение" << endl;
        cout << "4. Проверить сообщения" << endl;
        cout << "5. Выход из аккаунта" << endl;
        cout << "6. Выход из программы" << endl;
        cout << "Выберите действие: ";

        string choice;
        cin >> choice;

        try {
            if (choice == "1") {
                registerUser();
            }
            else if (choice == "2") {
                login();
            }
            else if (choice == "3") {
                sendMessage();
            }
            else if (choice == "4") {
                checkMessages();
            }
            else if (choice == "5") {
                logout();
            }
            else if (choice == "6") {
                cout << "Выход из программы..." << endl;
                break;
            }
            else {
                cout << "Некорректный ввод. Попробуйте снова " << endl;
            }
        }
        catch (const exception& e) {
            cout << "Произошла ошибка: " << e.what() << endl;
        }
    }
}