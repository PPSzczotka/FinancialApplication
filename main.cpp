#include <iostream>
#include "UserFile.h"

using namespace std;

int main()
{


    UserFile userFile("Users.xml");

    cout << "Nazwa pliku: " << userFile.getFileName() << endl;
    vector<User> users = userFile.loadUsersFromFile();
    cout << "Liczba uzytkownikow: " << users.size() << endl;

    User user;

    user.id =3;
    user.firstName=  "Pawel";
    user.lastName ="Nowak";
    user.login ="nowak543";
    user.password="nowak987";

    userFile.addUserToFile(user);

    return 0;
}
