#pragma once
#include <string>

class Phone {
private:
    std::string number_;

public:
    Phone() : number_("") {}
    Phone(const std::string& number) : number_(number) {}

    const std::string& get_number() const { return number_; }
    void set_number(const std::string& number) { number_ = number; }
};