#include <iostream>
#include "UserManager.h"
#include "HelperMethods.h"

using namespace std;

int main()
{
    UserManager userManager("Users.xml");
    char wybor;
    while (true)
    {
        if (userManager.getLoggedUserId()==0)
        {
            system("cls");
            cout <<">>> MENU UZYTKOWNIKA<<<" << endl;
            cout << "1.Rejestracja"<< endl;
            cout<<"2.Logowanie"<<endl;
            cout<<"9.Koniec programu"<< endl;
            cout <<"Twoj wybor"<<endl;

            wybor= HelperMethods::wczytajZnak();
            switch (wybor)
            {
            case '1':
                userManager.registerUser();
                break;

            case'2':
                    userManager.loginUser();
                break;

            case '9':
                exit(0);
            default:
                cout << endl << "Nie ma takiej opcji w menu." << endl << endl;
                system("pause");
                break;
            }
        }
        else
        {
            system("cls");
            cout << " >>> MENU UZYTKOWNIKA <<<" << endl;
            cout << "---------------------------" << endl;
            cout << "1. Dodaj przychod" << endl;
            cout << "2. Dodaj wydatek" << endl;
            cout << "3. Wyswietl bilans biezacego m-c" << endl;
            cout << "4. Wyswietl bilans poprzedniego m-c " << endl;
            cout << "5. Wyswietl bilans z wybranego okresu" << endl;
            cout << "6. Zmien haslo" << endl;
            cout << "9. Wyloguj sie" << endl;
            cout << "---------------------------" << endl;
            cout << "Twoj wybor: ";

            wybor= HelperMethods::wczytajZnak();
            switch (wybor)
            {
            case '1':
                //tutaj metoda
                break;

            case '2':
                //tutaj metoda
                break;

            case '3':
                //tutaj metoda
                break;

            case '4':
                //tutaj metoda
                break;

            case '5':
                //tutaj metoda
                break;

            case '6':
                userManager.changeUserPassword();
                break;

            case '9':
                userManager.logoutUser();
                break;
            default:
                cout << endl << "Nie ma takiej opcji w menu." << endl << endl;
                system("pause");
                break;
            }

        }
    }
    return 0;
}

