#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include "Employee.h"
using namespace std;
class Supervisor : public Employee
{
public:
    Supervisor();
    Supervisor(string, string, string, int, int, int, string);
    Supervisor(const Supervisor &);
    virtual ~Supervisor() = default;

    void print_employee() const override;
    int salary() const override;
    string get_type() const override { return "Supervisor"; }
};