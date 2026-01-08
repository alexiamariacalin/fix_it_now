#pragma once
#include <iostream>
#include <ctime>
#include <string>
using namespace std;
time_t present = time(NULL);
    struct tm now = *localtime(&present);
bool validate_CNP(string);
bool validate_date(const int, const int, const int, const int, const int, const int); // day,month,year,hour,minute,second
int age(string);                                                                      // calculate from CNP
string tm_date_to_string(const struct tm &);
bool cmp_tm_dates(struct tm, struct tm);