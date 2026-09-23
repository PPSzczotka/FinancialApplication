#ifndef USERFILE_H
#define USERFILE_H

#include <vector>
#include "File.h"
#include "User.h"

using namespace std;

class UserFile : public File
{
public:
    UserFile (string userFileName);

    vector<User> loadUsersFromFile();
    bool addUserToFile (const User &user);
    bool changePasswordInFile(int id, const string &password);
};

#endif
