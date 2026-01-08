#pragma once
#include <iostream>
#include <ctime>
#include <string>
using namespace std;
class Appliance
{
protected:
    string type; // Fridge, TV, Washing Machine
    string brand;
    string model;
    int manufacture_year;
    int catalog_price;

public:
    Appliance();
    Appliance(string, string, string, int, int);
    Appliance(const Appliance &);
    virtual ~Appliance() = default;

    virtual void print_appliance() const = 0;
    virtual bool operator==(const Appliance &) const = 0;

    virtual string get_type() const = 0;
    string get_brand() const { return brand; }
    string get_model() const { return model; }
    int get_manufacture_year() const { return manufacture_year; }
    int get_catalog_price() const { return catalog_price; }
};