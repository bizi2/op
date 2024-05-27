#pragma once
#include "FIO.h"
#include "data.h"
#include "Time.h"
#include <string>

class Employee {
private:
    FIO fio_;
    std::string position_;
    Date date_of_employment_;
    std::string specialization_;
    Time work_schedule_;

public:
    Employee(const FIO& fio, const std::string& position, const Date& date_of_employment, const std::string& specialization, const Time& work_schedule);

    const FIO& get_fio() const;
    const std::string& get_position() const;
    const Date& get_date_of_employment() const;
    const std::string& get_specialization() const;
    const Time& get_work_schedule() const;
};
