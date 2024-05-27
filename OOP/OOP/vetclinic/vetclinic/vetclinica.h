#pragma once
#include <string>
#include <vector>
#include "Phone.h"
#include "Employee.h"
#include "Client.h"
#include "Animal.h"
#include "ReceptionSchedule.h"
#include "MedicalHistory.h"

class VeterinaryClinic {
private:
    std::string name_;
    std::string address_;
    Phone phone_;
    std::string email_;
    std::vector<Employee> employees_;
    std::vector<Client> clients_;
    std::vector<Animal> animals_;
    
    

public:
    VeterinaryClinic(const std::string& name, const std::string& address, const Phone& phone, const std::string& email, const std::vector<Employee>& employees, const std::vector<Client>& clients, const std::vector<Animal>& animals, const ReceptionSchedule& reception_schedule, const MedicalHistory& medical_history);

    const std::string& get_name() const;
    const std::string& get_address() const;
    const Phone& get_phone() const;
    const std::string& get_email() const;
    const std::vector<Employee>& get_employees() const;
    const std::vector<Client>& get_clients() const;
    const std::vector<Animal>& get_animals() const;
   
    
};