#include "FinancialOperationManager.h"
#include "FinancialOperation.h"
#include "HelperMethods.h"
#include  "File.h"
#include "DateMethods.h"
#include "AmountMethods.h"

FinancialOperationManager:: FinancialOperationManager (
string incomeFileName,
string expenseFileName,
int loggedUserId): incomesFile(incomeFileName), expensesFile(expenseFileName),LOGGED_USER_ID(loggedUserId )
{
    incomes = incomesFile.loadOperationsFromFile(LOGGED_USER_ID, Type::INCOME);
    expenses = expensesFile.loadOperationsFromFile(LOGGED_USER_ID, Type::EXPENSE);
}

FinancialOperation FinancialOperationManager::addOperationDetails(const Type &type)
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

    do
    {
        cout<< "Podaj date operacji: ";
        financialOperation.date=HelperMethods::wczytajLinie();
        if(!dateMethods.validateDate(financialOperation.date))
        {
            cout <<"Podana data jest nieprawidlowa. Wprowadz ponownie date"<< endl;
        }
    }
    while(!dateMethods.validateDate(financialOperation.date));

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
    financialOperation.amount= stod(kwota);

    financialOperation.type= type;

    return financialOperation;
}


void FinancialOperationManager::addIncome()
{
    FinancialOperation financialOperation;
    financialOperation = addOperationDetails(Type::INCOME);

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
    FinancialOperation financialOperation;
    financialOperation = addOperationDetails(Type::EXPENSE);

    if(expensesFile.addOperationToFile(financialOperation))
    {
        cout<< "Twoje dane zostaly zapisane poprawnie"<< endl;
        expenses.push_back(financialOperation);
    }
    else
    {
        cout<< "Blad zapisu danych. Wprowadz ponownie"<< endl;
    }
}

double FinancialOperationManager:: calculateBalance(int startDate, int endDate, const Type &type)
{
    double suma = 0;

    DateMethods dateMethods;

    if (type == Type::INCOME)
    {
        for (FinancialOperation financialOperation : incomes )
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
        for (FinancialOperation financialOperation : expenses )
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
    double przychod = calculateBalance(startDate,endDate,Type::INCOME);
    double wydatki = calculateBalance(startDate,endDate,Type::EXPENSE);
    double bilans = przychod-wydatki;

    cout<< "Przychody :"<< przychod << endl;
    cout<< "Wydatki :"<< wydatki << endl;
    cout<< "Bilans :"<< bilans << endl;
}

void FinancialOperationManager::displayCurrentBalance()
{

}
