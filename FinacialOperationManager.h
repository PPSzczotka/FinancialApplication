#ifndef  FINANCIALOPERATIONMANAGER_H
#define FINANCIALOPERATIONMANAGER_H

#include <vector>
#include <string>

#include "FinancialOperation.h"
#include "Type.h"


using namespace std;

class FinancialOperationManager
{
private:
    const int LOGGED_USER_ID;
    vector<FinancialOperation> incomes;
    vector<FinancialOperation> expense;

    FinancialOperation addOperationDetails(const Type &type);
    void showBalance(int startDate, int endDate);
    double calculateBalance(int startDate, int endDate, const Type &type);

public:
    FinancialOperationManager (string incomeFileName, string expenseFileName, int loggedUserId);
    void addIncome();
    void addExpense();
    void  displayCurrentBalance();
    void displayPreviousBalance();
    void  displayBalanceForPeriod();

};
