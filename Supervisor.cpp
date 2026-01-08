#include "Supervisor.h"
Supervisor::Supervisor() : Employee() {}
Supervisor::Supervisor(string n, string s, string cnp, int d, int m, int y, string h) : Employee(n, s, cnp, d, m, y, h) {}
Supervisor::Supervisor(const Supervisor &s) : Employee(s) {}
void Supervisor::print_employee() const
{
    cout << "SUPERVISOR:" << endl;
    Employee::print_employee();
    cout<<endl;
}
int Supervisor::salary() const
{
    int salary = Employee::salary() + 800; // + 20% of base salary
    return salary;
}