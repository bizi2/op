#pragma once
#include "FIO.h"
#include "Phone.h"
#include "Animal.h"
#include <vector>

class Client {
private:
    FIO fio_;
    std::string address_;
    Phone phone_;
    std::string email_;
    std::vector<Animal> pets_;

public:
    Client(const FIO& fio, const std::string& address, const Phone& phone, const std::string& email, const std::vector<Animal>& pets);

    const FIO& get_fio() const;
    const std::string& get_address() const;
    const Phone& get_phone() const;
    const std::string& get_email() const;
    const std::vector<Animal>& get_pets() const;
};