#include "UserFile.h"
#include <string>
#include <iostream>
UserFile :: UserFile (string userFileName) : File(userFileName)
{

}

vector<User> UserFile:: loadUsersFromFile()
{
    vector<User> users;
    if (!xml.Load(getFileName()))
    {
        cout << "Nie udalo sie otworzyc pliku XML!" << endl;
        return users;
    }

    xml.ResetPos();
    if(!xml.FindElem( "Users" ))
    {
        return users;
    }
    xml.IntoElem();

    while (xml.FindElem("User"))
    {
        User user;

        xml.IntoElem();
        xml.FindElem("id");
        user.id = stoi(xml.GetData());
        if (user.id>lastId)
        {
            lastId= user.id;
        }

        xml.FindElem("firstName");
        user.firstName = xml.GetData();

        xml.FindElem("lastName");
        user.lastName = xml.GetData();

        xml.FindElem("login");
        user.login = xml.GetData();

        xml.FindElem("password");
        user.password = xml.GetData();

        users.push_back(user);

        xml.OutOfElem();
    }
    xml.OutOfElem();
    return users;
}

bool UserFile:: addUserToFile(const User &user)
{
    if (!xml.Load(getFileName()))
    {
        return false;
    }

    xml.ResetPos();
    if(!xml.FindElem("Users"))
    {
        return false;
    }
    xml.IntoElem();

    xml.AddElem("User");
    xml.IntoElem();

    xml.AddElem("id",user.id);
    xml.AddElem("firstName",user.firstName);
    xml.AddElem("lastName",user.lastName);
    xml.AddElem("login",user.login);
    xml.AddElem("password",user.password);

   if (!xml.Save(getFileName()))
    {
        return false;
    }
    lastId= user.id;
    return true;
}

bool UserFile::changePasswordInFile(int id, const string &password)
{
    if (!xml.Load(getFileName()))
    {
        return false;
    }

    xml.ResetPos();
    if (!xml.FindElem("Users"))
    {
        return false;
    }

    xml.IntoElem();
    while (xml.FindElem("User"))
    {
        xml.IntoElem();

        if (!xml.FindElem("id"))
        {
            return false;
        }

        int userId = stoi(xml.GetData());
        if (userId == id)
        {

            if (!xml.FindElem("password"))
            {
                return false;
            }

            xml.SetData(password);
            bool zapisano = xml.Save(getFileName());

            if (!zapisano)
            {
                return false;
            }
            return true;
        }

        xml.OutOfElem();
    }

    return false;
}
