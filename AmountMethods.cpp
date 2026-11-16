#include "AmountMethods.h"


bool AmountMethods::validateAmount(string amount)
{
  amount = convertCommaToDot(amount);
    try
    {
        size_t position;
        double kwota = stod(amount, &position);
        if (position== amount.length() && kwota >0.00)
        {
            return true;
        }
    }
    catch (...)
    {
       return false;
    }
    return false;
}

string AmountMethods::convertCommaToDot(string amount)
{
    size_t pozycja = amount.find(',');

    if(pozycja != string::npos)
    {
        amount.replace(pozycja,1,".");
    }
    return amount;
}
