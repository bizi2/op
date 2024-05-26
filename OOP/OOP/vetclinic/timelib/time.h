#pragma once
enum Status { SUCCESS = 3, ERROR = 1, WARNING = 2 };
using namespace std;
class Time {
private:
    int hours, minutes, seconds;

public:
    Time() : hours(0), minutes(0), seconds(0) {}
    Time(int hours, int minutes, int seconds);
    Status input();
    Status setValues(int hours, int minutes, int seconds);
    Status check();
    Status convert();
    Status addHours(int hours);
    Status addMinutes(int minutes);
    Status addSeconds(int seconds);
    int compare(const Time& other) const;
    Status assign(const Time& other);
    Status output() const;
};