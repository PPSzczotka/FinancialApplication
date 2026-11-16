#include "FinancialOperationManager.h"
#include "FinancialOperation.h"
#include "HelperMethods.h"
#include  "File.h"
#include "DateMethods.h"
#include "AmountMethods.h"

#include <algorithm>
#include <iomanip>

FinancialOperationManager:: FinancialOperationManager (
string incomeFileName,
string expenseFileName,
int loggedUserId): incomesFile(incomeFileName), expensesFile(expenseFileName),LOGGED_USER_ID(loggedUserId )
{
    incomes = incomesFile.loadOperationsFromFile(LOGGED_USER_ID, Type::INCOME);
    expenses = expensesFile.loadOperationsFromFile(LOGGED_USER_ID, Type::EXPENSE);
}

FinancialOperation FinancialOperationManager::addOperationDetails(Type type)
{
    AmountMethods amountMethods;

    FinancialOperation financialOperation;

    if(type == Type::INCOME)
    {
        financialOperation.id=incomesFile.getLastId()+1;
    }
    else
    {
        financialOperation.id=expensesFile.getLastId()+1;
    }
    financialOperation.userId=LOGGED_USER_ID;

    DateMethods dateMethods;
    char wybor;
    do
    {
        cout<< "WYBIERZ DATE"<< endl;
        cout <<"1.Dzisiejsz data"<< endl;
        cout<< "2.Podaj date"<< endl;
        wybor = HelperMethods::wczytajZnak();
        if( wybor == '1')
        {
            financialOperation.date = to_string(dateMethods.getCurrentDate());
        }
        else if (wybor == '2')
        {
            bool poprawnaData = false;
            do
            {
                cout<< "Podaj date operacji: ";
                financialOperation.date=HelperMethods::wczytajLinie();
                if(!dateMethods.validateDate(financialOperation.date))
                {
                    cout <<"Podana data jest nieprawidlowa. Wprowadz ponownie date"<< endl;
                }
                else
                {
                    int data = dateMethods.convertStringDateToInt(financialOperation.date);
                    if(data < 20000101 || data > dateMethods.getCurrentMonthLastDayDate())
                    {
                        cout << "Podana data jest poza dozwolonym zakresem. Wprowadz ponownie date"<< endl;
                    }
                    else
                        poprawnaData = true;
                }
            }

            while(!poprawnaData);
        }
    }
    while (wybor!='1' && wybor!='2');

    cout<< "Podaj opis operacji: ";
    financialOperation.item=HelperMethods::wczytajLinie();

    string kwota;

    do
    {
        cout<< "Podaj kwote operacji: ";
        kwota= HelperMethods::wczytajLinie();
        if (!amountMethods.validateAmount(kwota))
        {
            cout<<"Podana kwota nie jest prawidlowa. Wprowadz ponownie" << endl;
        }
    }
    while (!amountMethods.validateAmount(kwota));
    kwota= amountMethods.convertCommaToDot(kwota);
    financialOperation.amount= stod(kwota);

    financialOperation.type= type;

    return financialOperation;
}

bool compareOperations( const FinancialOperation &first, const FinancialOperation &second)
{
    if(first.date != second.date)
    {
        return first.date< second.date;
    }

    return first.type == Type::INCOME && second.type == Type::EXPENSE;
}


void FinancialOperationManager::addIncome()
{
   FinancialOperation financialOperation = addOperationDetails(Type::INCOME);

    if(incomesFile.addOperationToFile(financialOperation))
    {
        cout<< "Twoje dane zostaly zapisane poprawnie"<< endl;
        incomes.push_back(financialOperation);
        system("pause");
    }
    else
    {
        cout<< "Blad zapisu danych. Wprowadz ponownie"<< endl;
        system("pause");
    }
}


void FinancialOperationManager::addExpense()
{
   FinancialOperation financialOperation = addOperationDetails(Type::EXPENSE);

    if(expensesFile.addOperationToFile(financialOperation))
    {
        cout<< "Twoje dane zostaly zapisane poprawnie"<< endl;
        expenses.push_back(financialOperation);
        system("pause");
    }
    else
    {
        cout<< "Blad zapisu danych. Wprowadz ponownie"<< endl;
        system("pause");
    }
}

double FinancialOperationManager:: calculateBalance(int startDate, int endDate,Type type)
{
    double suma = 0;

    DateMethods dateMethods;

    if (type == Type::INCOME)
    {
        for (const FinancialOperation &financialOperation : incomes )
        {
            int dataOperacji = dateMethods.convertStringDateToInt(financialOperation.date);
            if (dataOperacji>= startDate && dataOperacji<=endDate)
            {
                suma = suma + financialOperation.amount;
            }
        }
    }
    else
    {
        for ( const FinancialOperation &financialOperation : expenses )
        {
            int dataOperacji = dateMethods.convertStringDateToInt(financialOperation.date);
            if (dataOperacji>= startDate && dataOperacji<=endDate)
            {
                suma = suma + financialOperation.amount;
            }
        }
    }
    return suma;
}

void FinancialOperationManager::showBalance(int startDate, int endDate)
{
    vector<FinancialOperation> operations;

    operations.insert(operations.end(), incomes.begin(), incomes.end());
    operations.insert(operations.end(), expenses.begin(), expenses.end());

    sort(operations.begin(), operations.end(), compareOperations);

    double przychod = calculateBalance(startDate,endDate,Type::INCOME);
    double wydatki = calculateBalance(startDate,endDate,Type::EXPENSE);
    double bilans = przychod-wydatki;

    cout<< fixed << setprecision(2);
    DateMethods dateMethods;
    for (vector<FinancialOperation>::iterator itr = operations.begin(); itr !=operations.end(); itr++)
    {
        int dataOperacji = dateMethods.convertStringDateToInt(itr->date);
        if(dataOperacji >= startDate && dataOperacji<= endDate)
        {
            cout << "Data operacji: "<< itr->date
                 << " | Opis operacji: "<< itr->item
                 << " | Kwota: "<< itr->amount << endl;
        }
    }

    cout<< "Przychody :"<< przychod << endl;
    cout<< "Wydatki :"<< wydatki << endl;
    cout<< "Bilans :"<< bilans << endl;
}

void FinancialOperationManager::displayCurrentBalance()
{
    DateMethods dateMethods;

    int startDate = dateMethods.getCurrentMonthFirstDayDate();
    int endDate = dateMethods.getCurrentDate();

    showBalance(startDate,endDate);
}


void FinancialOperationManager::displayPreviousBalance()
{
    DateMethods dateMethods;

    int startDate = dateMethods.getPreviousMonthFirstDayDate();
    int endDate = dateMethods.getPreviousMonthLastDayDate();

    showBalance(startDate,endDate);
}

void FinancialOperationManager::displayBalanceForPeriod()
{
    DateMethods dateMethods;

    string startDate;
    string endDate;

    int startDateInt;
    int endDateInt;

    do
    {
            do
            {
                cout << "Podaj date poczatkowa:"<< endl;
                startDate = HelperMethods::wczytajLinie();
                if(!dateMethods.validateDate(startDate))
                {
                    cout<< "Poczatkowa data jest nieprawidlowa. Wprowadz ponownie" << endl;
                }
            }
            while(!dateMethods.validateDate(startDate));


            do
            {
                cout << "Podaj date koncowa:"<< endl;
                endDate = HelperMethods::wczytajLinie();
                if(!dateMethods.validateDate(endDate))
                {
                    cout<< "Koncowa data jest nieprawidlowa. Wprowadz ponownie" << endl;
                }
            }
            while(!dateMethods.validateDate(endDate));
        startDateInt = dateMethods.convertStringDateToInt(startDate);
        endDateInt = dateMethods.convertStringDateToInt(endDate);
        if (startDateInt > endDateInt)
        {
            cout << "Zakres dat jest nieprawidlowy" << endl;
        }
    }
    while (startDateInt > endDateInt);

    showBalance(startDateInt,endDateInt);
}
