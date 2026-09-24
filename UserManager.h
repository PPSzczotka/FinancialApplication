#ifndef  USERMANAGER_H
#define USERMANAGER_H

#include "User.h"
#include "UserFile.h"

using namespace std;

class UserManager
{
private:
    int loggedUserId;
    vector<User>users;
    UserFile userFile;
    bool checkIfLoginExist(const string &login);

public:
    UserManager (string userFileName);
    void registerUser();
    bool loginUser();
    bool isUserLoggedIn();
    void logoutUser();
    int getLoggedUserId();
    void changeUserPassword();
};

#endif
