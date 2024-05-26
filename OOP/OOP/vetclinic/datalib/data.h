#pragma once

enum Status { SUCCESS = 3, ERROR = 1, WARNING = 2 };
using namespace std;

class Date {
private:
    int day, month, year;

public:
    Date() : day(0), month(0), year(0) {}
    Date(int day, int month, int year);
    Status input();
    Status setValues(int day, int month, int year);
    Status check();
    Status addDays(int days);
    Status addMonths(int months);
    Status addYears(int years);
    int compare(const Date& other) const;
    Status assign(const Date& other);
    Status output() const;
};