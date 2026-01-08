#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include "Appliance.h"
using namespace std;
class WashingMachine : public Appliance
{
    int capacity; // in kg

public:
    WashingMachine() = default;
    WashingMachine(string, string, string, int, int, int);
    WashingMachine(const WashingMachine &);
    ~WashingMachine() = default;

    void print_appliance() const override;
    bool operator==(const Appliance &) const override;

    int get_capacity() const { return capacity; }
    string get_type() const override { return "Washing Machine"; }
};