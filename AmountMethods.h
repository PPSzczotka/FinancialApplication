#ifndef  AMOUNTMETHODS_H
#define AMOUNTMETHODS_H

#include <string>
using namespace std;

class AmountMethods
{
    public:
    bool validateAmount(string amount);
    string convertCommaToDot(string amount);
};

#endif
