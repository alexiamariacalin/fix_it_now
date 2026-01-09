#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <map>
#include <algorithm>
#include <thread>
#include <chrono>
#include "Employee.h"
#include "Supervisor.h"
#include "Receptionist.h"
#include "Technician.h"
#include "Appliance.h"
#include "Fridge.h"
#include "WashingMachine.h"
#include "TV.h"
#include "Request.h"
#include "UsefulFunctions.h"
#include "ReadWrite.h"
using namespace std;
class Service // singleton class
{

    vector<unique_ptr<Employee>> employees;
    Technician *longest_repair_technician;

    vector<unique_ptr<Appliance>> appliances;
    vector<Appliance *> repaired_appliances;
    map<pair<string, pair<string, string>>, int> unrepairable_appliances; // find by type,brand,model

    vector<shared_ptr<Request>> requests;
    vector<shared_ptr<Request>> pending_requests;
    vector<shared_ptr<Request>> invalid_requests;

    priority_queue<shared_ptr<Request>, vector<shared_ptr<Request>>,
                   bool (*)(const shared_ptr<Request> &, const shared_ptr<Request> &)>
        valid_requests; // priority by submission date

    Service() : valid_requests([](const shared_ptr<Request> &a, const shared_ptr<Request> &b)
                               { return cmp_tm_dates(a->get_submission_request_date(), b->get_submission_request_date()); }) {}

public:
    static Service &get()
    {
        static Service instance;
        return instance;
    }
    void print_employees() const;
    void add_employee(unique_ptr<Employee>);
    vector<unique_ptr<Employee>>::iterator find_employee_by_id(int); // by ID, returns position in vector
    vector<unique_ptr<Employee>>::iterator find_employee_by_CNP(string);
    void modify_employee(vector<unique_ptr<Employee>>::iterator, string); // by position in vector
    void delete_employee(int);                                            // by ID
    void sort_employees_by_salary();
    void top_3_employees() const; // by salary
    Receptionist *get_receptionist() const;

    void print_appliances() const;
    void add_appliance(unique_ptr<Appliance>);
    void add_repaired_appliance(Appliance *);
    void print_repaired_appliances() const;
    void print_unrepairable_appliances() const;
    int total_unrepairable_appliances() const;
    void add_unrepairable_appliance(string, string, string); // type,brand, model
    void delete_appliance();
    vector<unique_ptr<Appliance>>::iterator find_appliance(const Appliance &);

    void print_requests() const;
    void print_valid_requests() const;
    void print_pending_requests() const;
    void print_pending_requests_in_file() const;
    void add_request(shared_ptr<Request>); //
    void add_valid_request(shared_ptr<Request>);
    void add_invalid_request(shared_ptr<Request>);
    void add_pending_request(shared_ptr<Request>);
    void sort_requests_by_date();

    void report_technician_longest_repair() const;
    void assign_request_to_technician(shared_ptr<Request>);
    void assign_requests_to_technicians();
    Technician *find_best_technician_for_request(shared_ptr<Request>) const;
    void simulation();

    bool validate_service() const;
    Service(Service const &) = delete;
    void operator=(Service const &) = delete;
};