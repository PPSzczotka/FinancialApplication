#include "DateMethods.h"
#include <ctime>

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

int DateMethods::getCurrentDate()
{
    time_t today= time(0);
    tm *date= localtime(&today);


    int year= date->tm_year + 1900;
    int month = date->tm_mon + 1;
    int day = date->tm_mday;

    int currentDate = year*10000 + month*100 + day;
    return currentDate;
}

int DateMethods:: getCurrentMonthFirstDayDate()
{
    time_t today= time(0);
    tm *date= localtime(&today);


    int year= date->tm_year + 1900;
    int month = date->tm_mon + 1;
    int day = 1;

    int firstDayOfMonth= year*10000 + month*100 + day;
    return firstDayOfMonth;
}

int DateMethods::getPreviousMonthLastDayDate()
{
    time_t today= time(0);
    tm *date= localtime(&today);


    int year= date->tm_year + 1900;
    int month = date->tm_mon + 1;
    if(month==1)
    {
        month =12;
        year = year-1;
    }
    else
    {
        month =month-1;
    }

    int day=0;
    if(month==2)
    {
        if (isYearLeap(year))
            day = 29;
        else
            day = 28;
    }
    else if(month== 4 || month==6 || month==9 ||month==11)
    {
        day =30;
    }
    else
    {
        day=31;
    }

    int previousMonthLastDay= year*10000 + month*100 + day;
    return previousMonthLastDay;
}

int DateMethods::getPreviousMonthFirstDayDate()
{
    time_t today= time(0);
    tm *date= localtime(&today);


    int year= date->tm_year + 1900;
    int month = date->tm_mon + 1;

    if(month==1)
    {
        year= year -1;
        month = 12;
    }
    else
    {
        month = month -1;
    }

    int day = 1;
    int previousMonthFirstDay= year*10000 + month*100 + day;
    return previousMonthFirstDay;
}
