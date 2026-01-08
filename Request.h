#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <memory>
#include "Appliance.h"
#include "UsefulFunctions.h"
using namespace std;
class Request
{
    static int total_requests;
    const int ID;
    unique_ptr<Appliance> appliance; // to be fixed
    struct tm submission_request_date;
    int complexity_level;
    int estimated_repair_time; // must be calculated
    int cost;                  // must be calculated
public:
    Request() = default;
    Request(unique_ptr<Appliance>, int, int, int, int, int, int, int);
    // Request(const Request &);
    ~Request();

    void print_request() const;

    const int get_ID() const { return ID; }
    Appliance *get_appliance() const { return appliance.get(); }
    tm get_submission_request_date() const { return submission_request_date; }
    int get_complexity_level() const { return complexity_level; }
    int get_estimated_repair_time() const { return estimated_repair_time; }
    int get_cost() const { return cost; }

    friend bool validate_date(int, int, int, int, int, int); // day,month,year,hour,minute,second
};