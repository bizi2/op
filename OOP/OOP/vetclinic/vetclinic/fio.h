#pragma once
#include <string>

class FIO {
private:
    std::string first_name_;
    std::string last_name_;
    std::string middle_name_;

public:
    FIO(const std::string& first_name, const std::string& last_name, const std::string& middle_name);

    const std::string& get_first_name() const;
    const std::string& get_last_name() const;
    const std::string& get_middle_name() const;
};
