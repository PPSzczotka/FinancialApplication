#include "UserFile.h"
#include <string>

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
    xml.FindElem( "Users" );
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
    xml.FindElem("Users");
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
        cout << "Nie udalo sie otworzyc pliku XML!" << endl;
        return false;
    }
    xml.ResetPos();
    xml.FindElem( "Users" );
    xml.IntoElem();
    while (xml.FindElem("User"))
    {
        User user;

        xml.IntoElem();
        xml.FindElem("id");
        user.id = stoi(xml.GetData());

        if (user.id == id)
        {
            xml.FindElem("password");
            xml.SetData(password);
            xml.Save(getFileName());
            return true;
        }
        xml.OutOfElem();
    }
    return false;
}
