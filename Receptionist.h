#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include "Employee.h"
using namespace std;
class Receptionist : public Employee
{
    vector<int> ID_list;

public:
    Receptionist();
    Receptionist(string, string, string, int, int, int, string);
    Receptionist(const Receptionist &);
    ~Receptionist() = default;

    void print_employee() const override;
    void add_request_ID(const int&);
    int salary() const override { return Employee::salary(); }
    string get_type() const override { return "Receptionist"; }

    vector<int> get_ID_list() const { return ID_list; }
};