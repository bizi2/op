#include "time.h"
#include <iostream>
Time::Time(int hours, int minutes, int seconds) {
    setValues(hours, minutes, seconds);
}
Status Time::input() {
    Status state = SUCCESS;
    char colon;
    cout << "Enter time in format HH:MM:SS: ";
    cin >> hours >> colon >> minutes >> colon >> seconds;
    return state;
}

Status Time::setValues(int hours, int minutes, int seconds) {
    Status state = SUCCESS;
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
    return state;
}

Status Time::check() {
    Status state = SUCCESS;
    if (seconds > 60 || seconds < 1 || minutes > 60 || minutes < 1 || hours > 24 || hours < 1)
        state = ERROR;
    return state;
}

Status Time::convert() {
    Status state = SUCCESS;
    while (true) {
        if (seconds > 60) {
            seconds -= 60;
            minutes++;
            continue;
        }
        else if (minutes > 60) {
            minutes -= 60;
            hours++;
            continue;
        }
        else if (hours > 24) {
            hours -= 24;
            state = WARNING;
        }
        else
            break;
    }
    return state;
}

Status Time::addHours(int hours) {
    Status state = SUCCESS;
    this->hours += hours;
    return state;
}

Status Time::addMinutes(int minutes) {
    Status state = SUCCESS;
    this->minutes += minutes;
    return state;
}

Status Time::addSeconds(int seconds) {
    Status state = SUCCESS;
    this->seconds += seconds;
    return state;
}

int Time::compare(const Time& other) const {
    int totalSeconds1 = hours * 3600 + minutes * 60 + seconds;
    int totalSeconds2 = other.hours * 3600 + other.minutes * 60 + other.seconds;

    if (totalSeconds1 > totalSeconds2)
        return 1;
    else if (totalSeconds1 < totalSeconds2)
        return -1;
    else
        return 0;
}

Status Time::assign(const Time& other) {
    Status state = SUCCESS;
    hours = other.hours;
    minutes = other.minutes;
    seconds = other.seconds;
    return state;
}

Status Time::output() const {
    Status state = SUCCESS;
    cout << hours << ":" << minutes << ":" << seconds << " " << endl;
    return state;
}