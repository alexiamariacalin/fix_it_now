#include "Employee.h"
Employee::Employee() : ID(++ID_generator), name("unspecified"), surname("unspecified"), CNP("unspecified"), employment_date{}, hometown("unspecified") {}
Employee::Employee(string n, string s, string cnp, int day, int month, int year, string h) : ID(++ID_generator), name(n), surname(s), CNP(cnp), hometown(h)
{
    if (n.size() < 3)
        throw invalid_argument("Name too short");
    if (n.size() > 30)
        throw invalid_argument("Name too long");

    if (s.size() < 3)
        throw invalid_argument("Surname too short");
    if (s.size() > 30)
        throw invalid_argument("Surname too long");

    if (validate_CNP(cnp) == false)
        throw invalid_argument("Invalid CNP");

    if (age(cnp) < 16)
        throw invalid_argument("Must be at least 16 years old to be employed");

    if (validate_date(day, month, year, 0, 0, 0) == false)
        throw invalid_argument("Invalid employment date");
    employment_date = {.tm_sec = 0, .tm_min = 0, .tm_hour = 0, .tm_mday = day, .tm_mon = month - 1, .tm_year = year - 1900};
    mktime(&employment_date);
}
Employee::Employee(const Employee &e) : ID(++ID_generator), name(e.name), surname(e.surname), CNP(e.CNP), employment_date(e.employment_date), hometown(e.hometown) {}
void Employee::print_employee() const
{
    cout << "Age: " << age(CNP) << endl;
    // cout << "Valid CNP: " << validate_CNP(CNP) << endl;
    //  cout<<"EMPLOYEE:"<<endl;
    cout << "ID: " << ID << endl;
    cout << "Name: " << name << endl;
    cout << "Surname: " << surname << endl;
    cout << "CNP: " << CNP << endl;
    cout << "Employment date: ";

    char output[50];
    strftime(output, sizeof(output), "%d/%m/%Y", &employment_date);
    cout << output << endl;

    cout << "Hometown: " << hometown << endl;
    cout << "Salary: " << salary() << endl;
}
int Employee::years_of_employment() const
{
    time_t now = time(NULL);
    struct tm end = *localtime(&now);
    struct tm start = employment_date;

    if (end.tm_yday >= start.tm_yday) // values between 0 and 365
        return end.tm_year - start.tm_year;
    return end.tm_year - start.tm_year - 1;
}
int Employee::salary() const
{
    int base = 4000;                                     // base salary
    int salary = base + years_of_employment() / 3 * 200; // + 5% of base salary for every 3 years
    if (hometown != "București")
        salary += 400; // + 400 for non-București employees
    return salary;
}
void Employee::modify_surname(string new_surname)
{
    surname = new_surname;
}
