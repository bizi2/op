#pragma once
#include <string>
#include "data.h"

class Animal {
private:
    std::string name_;
    std::string species_;
    Date date_of_birth_;
    double weight_;
    std::string breed_;

public:
    Animal(const std::string& name, const std::string& species, const Date& date_of_birth, double weight, const std::string& breed);

    const std::string& get_name() const;
    const std::string& get_species() const;
    const Date& get_date_of_birth() const;
    double get_weight() const;
    const std::string& get_breed() const;
};