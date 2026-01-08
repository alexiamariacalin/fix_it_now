#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include "Employee.h"
#include <map>
#include <vector>
using namespace std;
class Technician : public Employee
{
    int active_repairs;              // number of appliances being currently repaired, max 3
    int total_bonus;                 // from repaired appliances, goes to salary
    multimap<string, string> skills; // repairable appliances

public:
    Technician() = default;
    Technician(string, string, string, int, int, int, string, multimap<string, string>);
    Technician(const Technician &);
    ~Technician() = default;

    void modify_bonus(int);
    void print_employee() const override;
    bool find_skill(const string &, const string &);
    int salary() const override { return Employee::salary() + total_bonus; } // Placeholder implementation;

    string get_type() const override { return "Technician"; }
    int get_active_repairs() const { return active_repairs; }
    multimap<string, string> get_skills() const { return skills; }
};