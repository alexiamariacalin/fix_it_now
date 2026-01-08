#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include "UsefulFunctions.h"
using namespace std;
class Employee
{
protected:
    static int ID_generator; // ID generator
    const int ID;            // unique
    string name, surname;    // 3-30 characters each
    string CNP;              // must be valid, check website
    tm employment_date;
    string hometown;

public:
    Employee();
    Employee(string, string, string, int, int, int, string);
    Employee(const Employee &);
    virtual ~Employee() = default;

    virtual void print_employee() const = 0;
    int years_of_employment() const;
    virtual int salary() const = 0;
    void modify_surname(string);

    const int get_ID() const { return ID; }
    string get_name() const { return name; }
    string get_surname() const { return surname; }
    string get_CNP() const { return CNP; }
    tm get_employment_date() const { return employment_date; }
    string get_hometown() const { return hometown; }
    virtual string get_type() const = 0;

    friend bool validate_CNP(string);
    friend bool validate_date(int, int, int, int, int, int); // day,month,year,hour,minute,second
    friend int age(string);                                  // calculate from CNP
};
