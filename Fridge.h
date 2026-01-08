#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include "Appliance.h"
using namespace std;
class Fridge : public Appliance
{
    bool freezer; // 1-has freezer, 0-no freezer
public:
    Fridge() = default;
    Fridge(string, string, string, int, int, bool);
    Fridge(const Fridge &);
    ~Fridge() = default;

    void print_appliance() const override;
    bool operator==(const Appliance &) const override;

    bool get_freezer() const { return freezer; }
    string get_type() const override { return "Fridge"; }
};