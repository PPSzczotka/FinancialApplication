#ifndef  DATEMETHODS_H
#define DATEMETHODS_H

#include <iostream>
#include <ctime>
#include <map>
#include <string>

using namespace std;

class DateMethods
{
private:
    bool  isYearLeap(int year);

public:
bool validateDate(const string &date);
int convertStringDateToInt(const string &dateAsString);

int getCurrentDate();
int getCurrentMonthFirstDayDate();
int getPreviousMonthLastDayDate();
int getPreviousMonthFirstDayDate();
int getCurrentMonthLastDayDate();

};
#endif
