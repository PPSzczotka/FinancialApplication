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

    cout<< "Podaj imie:";
    user.firstName=HelperMethods::wczytajLinie();

    cout<< "Podaj nazwisko:";
    user.lastName=HelperMethods::wczytajLinie();

    do
    {
        cout<< "Podaj login:";
        user.login=HelperMethods::wczytajLinie();
    }
    while(checkIfLoginExist(user.login));

    cout<< "Podaj haslo:";
    user.password=HelperMethods::wczytajLinie();


    if (userFile.addUserToFile(user))
    {
        users.push_back(user);

    }

}

bool UserManager::checkIfLoginExist(const string &login)
{
    for (User user : users)
    {
        if (login==user.login)
        {
            cout<<"Uzytkownik o takim loginie istnieje.Podaj nowy login"<< endl;
            return true;
        }
    }
    return false;
}

bool UserManager::loginUser()
{
    string login = "", haslo = "";
    cout << endl << "Podaj login:";
    login = HelperMethods::wczytajLinie();

    vector<User>::iterator itr = users.begin();
    while (itr != users.end())
    {
        if(itr ->login == login)
        {
            cout << endl << "Podaj haslo:";
            haslo = HelperMethods::wczytajLinie();
            if (itr->password == haslo)
            {
                loggedUserId= itr-> id;
                return true;
            }
        }
        itr++;
    }
    return false;
}

bool UserManager::isUserLoggedIn()
{
    if (loggedUserId > 0)
    {
        return true;
    }
    return false;
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
    cout << "Podaj nowe haslo:"<< endl;
    noweHaslo = HelperMethods::wczytajLinie();

   if(userFile.changePasswordInFile(loggedUserId,noweHaslo))
      {
          cout<< "Haslo zostalo zmienione!"<< endl;
      }
    else
    {
        cout<<"Zmiana hasla nie powiodla sie" << endl;
    }
 }
