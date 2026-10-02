#include "FinancialOperationManager.h"
#include "FinancialOperation.h"
#include "HelperMethods.h"
#include  "File.h"

FinancialOperationManager:: FinancialOperationManager (
string incomeFileName,
string expenseFileName,
int loggedUserId): incomesFile(incomeFileName), expensesFile(expenseFileName),LOGGED_USER_ID(loggedUserId )
{
    incomes = incomesFile.loadOperationsFromFile(LOGGED_USER_ID);
    expenses = expensesFile.loadOperationsFromFile(LOGGED_USER_ID);
}

FinancialOperation FinancialOperationManager::addOperationDetails(const Type &type)
{
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

    cout<< "Podaj date operacji: ";
    financialOperation.date=HelperMethods::wczytajLinie();

    cout<< "Podaj kwote operacji: ";
    string kwota;
    kwota= HelperMethods::wczytajLinie();
    financialOperation.amount= stod(kwota);

    financialOperation.type= type;

    return financialOperation;
}


void FinancialOperationManager::addIncome()
{
    FinancialOperation financialOperation;
    financialOperation = addOperationDetails(Type::INCOME);
    cout << "Kwota przed zapisem: " << financialOperation.amount << endl;
    system("pause");
    if(incomesFile.addOperationToFile(financialOperation))
    {
        cout<< "Twoje dane zostaly zapisane poprawnie"<< endl;
        incomes.push_back(financialOperation);

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


void FinancialOperationManager::displayCurrentBalance()
{

}
