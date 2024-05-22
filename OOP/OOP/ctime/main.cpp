
#include "time.h"
#include <iostream>


int main() {
    cout << "TIME:";
    Time time1(14, 12, 35), time2;

    cout << " " << time2.assign(time1) << endl;
    cout << time1.output() << endl;
    cout << time1.addHours(20) << endl;
    cout << time1.addMinutes(10) << endl;
    cout << time1.addSeconds(5) << endl;
    cout << time1.output() << endl;
    cout << time1.convert() << endl;
    cout << time1.output() << endl;
    cout << time1.compare(time2) << endl;


    

    return 0;
}