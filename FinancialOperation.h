#include <iostream>
#ifndef FINANCIALOPERATION_H
#define  FINANCIALOPERATION_H
#include "Type.h"

using namespace std;

struct FinancialOperation
{
    int id;
    int userId;
    string date;
    double amount;
    Type type;
};

#endif
