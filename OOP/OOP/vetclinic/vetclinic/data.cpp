#include "data.h"
#include <iostream>
Date::Date(int day, int month, int year) {
    setValues(day, month, year);
}

Status Date::input() {
    Status state = SUCCESS;
    char dot;
    cout << "Enter date in format DD.MM.YYYY: ";
    cin >> day >> dot >> month >> dot >> year;
    return state;
}

Status Date::setValues(int day, int month, int year) {
    Status state = SUCCESS;
    this->day = day;
    this->month = month;
    this->year = year;
    return state;
}

Status Date::check() {
    Status state = SUCCESS;
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        state = ERROR;
    }
    return state;
}

Status Date::addDays(int days) {
    Status state = SUCCESS;

    day += days;

    if (day > 31) {
        day -= 31;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    return state;
}
Status Date::addMonths(int months) {
    Status state = SUCCESS;
    month += months;

    while (month > 12) {
        month -= 12;
        year++;
    }

    return state;
}
Status Date::addYears(int years) {
    Status state = SUCCESS;
    year += years;
    return state;
}

int Date::compare(const Date& other) const {

    if (year > other.year)
        return 1;
    else if (year < other.year)
        return -1;
    else if (month > other.month)
        return 1;
    else if (month < other.month)
        return -1;
    else if (day > other.day)
        return 1;
    else if (day < other.day)
        return -1;
    else
        return 0;
}

Status Date::assign(const Date& other) {
    Status state = SUCCESS;
    day = other.day;
    month = other.month;
    year = other.year;
    return state;
}

Status Date::output() const {
    Status state = SUCCESS;
    cout << day << "." << month << "." << year << " " << endl;
    return state;
}