#include "DateMethods.h"


int DateMethods::convertStringDateToInt(const string &dateAsString)
{
   return  stoi(dateAsString);
}

bool DateMethods::isYearLeap(int year)
{
    if (year % 400 == 0)
        return true;

    if (year % 100 == 0)
        return false;

    if (year % 4 == 0)
        return true;

    return false;
}

bool DateMethods:: validateDate(string &date)
{
    int year;
    int month;
    int day;

    year = stoi(date.substr(0,4));
    month = stoi(date.substr(4,2));
    day=stoi(date.substr(6,2));

    if (month < 1 || month > 12)
    {
        return false;
    }
    if (day < 1)
    {
        return false;
    }
    int maxDays;
    switch (month)
    {
    case 2:
        if (isYearLeap(year))
            maxDays = 29;
        else
            maxDays = 28;
        break;

    case 4:
    case 6:
    case 9:
    case 11:
        maxDays = 30;
        break;

    default:
        maxDays = 31;
    }
    if (day > maxDays)
    {
        return false;
    }

    return true;
}
