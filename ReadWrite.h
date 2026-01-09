#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <algorithm>
#include "Service.h"
using namespace std;
unique_ptr<Employee> read_employee_from_file(string e);
unique_ptr<Appliance> read_appliance_from_file(string a);
shared_ptr<Request> read_request_from_file(string r);
unique_ptr<Employee> read_employee_from_menu();
unique_ptr<Appliance> read_appliance_from_menu();
void read_employees_from_file(const string &file);
void read_appliances_from_file(const string &file);
void read_requests_from_file(const string &file);
void print_employee_in_file(ofstream &, Employee *);
void print_pending_request_in_file(ofstream &, Request *);
void print_appliance_in_file(ofstream &, Appliance *);