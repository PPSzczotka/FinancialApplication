#ifndef  DATEMETHODS_H
#define DATEMETHODS_H

#include <iostream>
#include <ctime>
#include <map>

using namespace std;

class DateMethods
{
private:
    //void calculateCurrentDate(map<string, int> &currentDate);
    bool  isYearLeap(int year);

public:
bool validateDate(string &date);
int convertStringDateToInt(const string &dateAsString);

//string convertIntDateToStringWithDashes(int dateAsInt);

int getCurrentDate();
int getCurrentMonthFirstDayDate();
int getPreviousMonthLastDayDate();
int getPreviousMonthFirstDayDate();

};
#endif
