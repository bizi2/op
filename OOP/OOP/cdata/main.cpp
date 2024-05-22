#include "data.h"
#include <iostream>


int main() {


    Date date1(14, 12, 2022), date2;
    cout << "DATE: ";
    cout << date2.assign(date1) << endl;
    cout << date1.output() << endl;
    cout << date1.addDays(20) << endl;
    cout << date1.output() << endl;
    cout << date1.compare(date2) << endl;
    cout << date1.addDays(-10) << endl;
    cout << date1.output() << endl;

    return 0;
}