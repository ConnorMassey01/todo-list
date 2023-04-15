#include "../headers/date.h"

std::string Date::getDate(int offset){
    std::time_t t = std::time(0);  
    std::tm* now = std::localtime(&t);
    int year = now->tm_year;
    int month = now->tm_mon;
    int day = now->tm_mday;
    //convert the day based on the offset from the current date
    day = day + offset;
    while(day > Date::DAYS_PER_MONTH[month]){
        //account for leap year
        if(year % 4 == 0 && month == 1){
            day--;
        }
        day = day - DAYS_PER_MONTH[month];
        month = month + 1;
        if (month == 12){
            month = 0;
            year++;
        }
    }
    return Date::MONTHS[month] + " " + std::to_string(day);
}