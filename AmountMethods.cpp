#include "AmountMethods.h"


bool AmountMethods::validateAmount(string amount)
{
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
