#include <iostream>
#include "UserManager.h"

using namespace std;

int main()
{
    UserManager userManager("Users.xml");
    if (userManager.loginUser())
{
    cout<<"Logowanie udane!" << endl;
}
else
{
    cout << "Logowanie nieudane"<< endl;
}
    return 0;
}
