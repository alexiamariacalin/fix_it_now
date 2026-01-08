#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include "Appliance.h"
using namespace std;
class TV : public Appliance
{
    int size; // in cm
public:
    TV() = default;
    TV(string, string, string, int, int, int);
    TV(const TV &);
    ~TV() = default;

    void print_appliance() const override;
    bool operator==(const Appliance &) const override;

    string get_type() const override { return "TV"; }
    int get_size() const { return size; }
};