#include "Receptionist.h"
Receptionist::Receptionist() : Employee(), ID_list({}) {}
Receptionist::Receptionist(string n, string s, string cnp, int d, int m, int y, string h) : Employee(n, s, cnp, d, m, y, h) {}
Receptionist::Receptionist(const Receptionist &r) : Employee(r), ID_list(r.get_ID_list()) {}
void Receptionist::print_employee() const
{
    cout << "RECEPTIONIST:" << endl;
    Employee::print_employee();
    cout << "Request ID List: ";
    for (auto id : ID_list)
        cout << id << " ";
    cout << endl
         << endl;
}
void Receptionist::add_request_ID(const int &id)
{
    ID_list.push_back(id);
}