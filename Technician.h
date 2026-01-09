#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include "Employee.h"
#include "Request.h"
#include <map>
#include <vector>
using namespace std;
class Technician : public Employee
{
    vector<pair<shared_ptr<Request>, int>> active_repairs; // list of repairs, max 3, each with its estimated repair time (to be modified)
    int total_bonus;                                       // from repaired appliances, goes to salary
    int workload;                                          // worked "hours"
    multimap<string, string> skills;                       // repairable appliances

public:
    Technician() = default;
    Technician(string, string, string, int, int, int, string, multimap<string, string>);
    Technician(const Technician &);
    ~Technician() = default;

    void modify_bonus(int);
    void add_repair(shared_ptr<Request>);
    bool work_on_repairs();
    vector<Appliance *> remove_finished_repairs();
    void add_to_workload() { workload++; }
    void print_employee() const override;
    bool find_skill(const string &, const string &);
    int salary() const override { return Employee::salary() + total_bonus; } // Placeholder implementation;

    string get_type() const override { return "Technician"; }
    vector<pair<shared_ptr<Request>, int>> get_active_repairs() const { return active_repairs; }
    multimap<string, string> get_skills() const { return skills; }
    int get_workload() const { return workload; }
};