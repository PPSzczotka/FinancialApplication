#include "UserManager.h"
#include "HelperMethods.h"

UserManager::UserManager(string userFileName)
:userFile(userFileName)
{
    loggedUserId = 0;
    users = userFile.loadUsersFromFile();
}

void UserManager:: registerUser()
{
    User user;

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
