#include "UserManager.h"
#include "HelperMethods.h"
#include  "File.h"

UserManager::UserManager(string userFileName)
    :userFile(userFileName)
{
    loggedUserId = 0;
    users = userFile.loadUsersFromFile();
}

void UserManager:: registerUser()
{
    User user;

    user.id=userFile.getLastId()+1;

    do
    {
    cout<< "Podaj imie:";
    user.firstName=HelperMethods::wczytajLinie();
    }
    while(user.firstName.empty());

    do
    {
    cout<< "Podaj nazwisko:";
    user.lastName=HelperMethods::wczytajLinie();
    }
    while(user.lastName.empty());

    do
    {
        cout<< "Podaj login:";
        user.login=HelperMethods::wczytajLinie();
        if (user.login.empty())
            cout << "Login nie moze byc pusty!" << endl;

    }
    while (user.login.empty() || checkIfLoginExist(user.login));

    do
    {
    cout<< "Podaj haslo:";
    user.password=HelperMethods::wczytajLinie();
    }
    while(user.password.empty());

    if (userFile.addUserToFile(user))
    {
        cout<< " Twoje dane zostaly zapisane poprawnie"<< endl;
        users.push_back(user);
        system("pause");
    }
    else
    {
        cout << "Blad zapisu danych.Rejestracja nie powiodla sie"<< endl;
        system("pause");
    }

}

bool UserManager::checkIfLoginExist(const string &login)
{
    for (const User &user : users)
    {
        if (login==user.login)
        {
            cout<<"Uzytkownik o podanym loginie istnieje. Podaj ponownie login"<< endl;
            return true;
        }
    }
    return false;
}

bool UserManager::loginUser()
{
    string login = "", haslo = "";

    do
    {
        cout << endl << "Podaj login:";
        login = HelperMethods::wczytajLinie();
        vector<User>::iterator itr = users.begin();
        while (itr != users.end())
        {
        if(itr ->login == login)
        {
            for(int probaHasla = 0; probaHasla<3; probaHasla++)
            {
                cout << endl << "Podaj haslo:";
                 haslo = HelperMethods::wczytajLinie();
                if (itr->password == haslo)
                {
                    loggedUserId= itr-> id;
                    cout<<"Zalogowales sie prawidlowo"<<endl;
                    return true;
                }
                else
                {
                    cout<<"Haslo jest nieprawidlowe"<<endl;
                }
            }
            return false;
        }
        itr++;
        }
        cout<<"Uzytkownik o podanym loginie nie istnieje. Podaj ponownie login"<< endl;
    }
    while(!checkIfLoginExist(login));
    return false;
}

bool UserManager::isUserLoggedIn()
{
    return loggedUserId > 0;
}

void UserManager:: logoutUser()
{
    loggedUserId = 0;
}

int UserManager:: getLoggedUserId()
{
    return loggedUserId;
}

void UserManager:: changeUserPassword()
{
    string noweHaslo = "";
    do
    {
    cout << "Podaj nowe haslo:"<< endl;
    noweHaslo = HelperMethods::wczytajLinie();
    }
    while(noweHaslo.empty());

    if(userFile.changePasswordInFile(loggedUserId,noweHaslo))
    {
        cout<< "Haslo zostalo zmienione!"<< endl;
        system("pause");
        vector<User>::iterator itr = users.begin();
        while (itr != users.end())
        {
            if(itr ->id == loggedUserId)
            {
                itr-> password = noweHaslo;
                break;
            }
            itr++;
        }
    }
    else
    {
        cout<<"Zmiana hasla nie powiodla sie" << endl;
        system("pause");
    }
}
