#include "UsefulFunctions.h"
bool validate_date(const int day, const int month, const int year, const int hour, const int minute, const int second)
{
    if (!(month >= 1 and month <= 12))
        return 0;
    if (!(day >= 1 and day <= 31))
        return 0;
    if (month == 2)
        if (!(year % 400 == 0 or (year % 4 == 0 and year % 100 != 0))) // not leap year
            if (!(day <= 28))
                return 0;
            else
                ;
        else if (!(day <= 29))
            return 0;
    if (month == 1 or month == 3 or month == 5 or month == 7 or month == 8 or month == 10 or month == 12)
        if (!(day <= 31))
            return 0;
        else
            ;
    else if (!(day <= 30))
        return 0;

    if (!(hour >= 0 and hour <= 23))
        return 0;
    if (!(minute >= 0 and minute <= 59))
        return 0;
    if (!(second >= 0 and second <= 59))
        return 0;

    return 1;
}
bool validate_CNP(string cnp) // S AA LL ZZ JJ NNN C
{
    if (cnp.size() != 13)
        return 0;
    if (!(cnp[0] >= '1' and cnp[0] <= '8'))
        return 0;

    int year = stoi(cnp.substr(1, 2));
    if (cnp[0] == '1' or cnp[0] == '2')
        year += 1900;
    else if (cnp[0] == '5' or cnp[0] == '6')
        year += 2000;
    int month = stoi(cnp.substr(3, 2));
    int day = stoi(cnp.substr(5, 2));
    // cout << year << " " << month << " " << day << endl;
    if (validate_date(day, month, year, 0, 0, 0) == 0)
        return 0;
    int county = stoi(cnp.substr(7, 2));
    // cout << county << endl;
    if (!(county >= 1 and county <= 48 or county == 51 or county == 52 or county == 70))
        return 0;

    int sum = 0;
    string constant = "279146358279";
    for (int i = 0; i < 12; i++)
        sum += (cnp[i] - '0') * (constant[i] - '0');
    sum %= 11;
    int C = cnp[12] - '0';
    if (sum < 10 and sum != C)
        return 0;
    if (sum == 10 and C != 1)
        return 0;
    return 1;
}
int age(string cnp)
{
    time_t present = time(NULL);
    struct tm now = *localtime(&present);

    int year = stoi(cnp.substr(1, 2));
    if (cnp[0] == '1' or cnp[0] == '2')
        year += 1900;
    else if (cnp[0] == '5' or cnp[0] == '6')
        year += 2000;
    int month = stoi(cnp.substr(3, 2));
    int day = stoi(cnp.substr(5, 2));

    struct tm aux = {.tm_mday = day, .tm_mon = month - 1, .tm_year = year - 1900};
    mktime(&aux); // fills in the rest of the fields

    if (now.tm_yday >= aux.tm_yday)
        return now.tm_year - aux.tm_year;
    return now.tm_year - aux.tm_year - 1;
}
string tm_date_to_string(const struct tm &date)
{
    string result = "";

    result += to_string(1900 + date.tm_year);
    (date.tm_mon + 1 < 10) ? result += "0" : result;
    result += to_string(date.tm_mon + 1);
    result += to_string(date.tm_mday);

    (date.tm_hour < 0) ? result += "0" : result;
    result += to_string(date.tm_hour);
    (date.tm_min < 0) ? result += "0" : result;
    result += to_string(date.tm_min);
    (date.tm_sec < 0) ? result += "0" : result;
    result += to_string(date.tm_sec);

    return result;
}
bool cmp_tm_dates(struct tm date1, struct tm date2)
{
    return mktime(&date1) > mktime(&date2);
}
