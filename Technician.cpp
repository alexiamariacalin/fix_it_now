#include "Technician.h"
Technician::Technician(string n, string s, string cnp, int d,int m,int y, string h, multimap<string, string> sk) : Employee(n, s, cnp, d,m,y, h), skills(sk) {}
Technician::Technician(const Technician &t) : Employee(t), skills(t.skills) {}
void Technician::print_employee() const
{
    cout << "TECHNICIAN:" << endl;
    Employee::print_employee();
    cout << "Able to repair: ";

    vector<string> v{"Fridge", "TV", "Washing Machine"};
    for (auto k : v)
    {
        auto range = skills.equal_range(k);
        if (range.first != range.second)
        {
            auto i = range.first;
            cout << k << "(";
            cout << i->second;
            for (++i; i != range.second; i++)
                cout << ", " << i->second;
            cout << ")";
            if (k != "Washing Machine")
                cout << ", ";
        }
    }
    cout << endl
         << endl;
}
void Technician::modify_bonus(int new_bonus)
{
    total_bonus += new_bonus;
}
bool Technician::find_skill(const string &type, const string &brand)
{
    auto range = skills.equal_range(type);
    for (auto i = range.first; i != range.second; i++)
        if (i->second == brand)
            return true;
    return false;
}