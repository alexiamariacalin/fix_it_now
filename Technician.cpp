#include "Technician.h"
Technician::Technician(string n, string s, string cnp, int d, int m, int y, string h, multimap<string, string> sk) : Employee(n, s, cnp, d, m, y, h), total_bonus(0), workload(0), skills(sk) {}
Technician::Technician(const Technician &t) : Employee(t), skills(t.skills) {}
void Technician::print_employee() const
{
    cout << "TECHNICIAN:" << endl;
    Employee::print_employee();
    cout << "Able to repair: " << endl;
    vector<string> v{"Fridge", "TV", "Washing Machine"};
    for (auto k : v)
    {
        cout << "   " << k << ": ";
        auto range = skills.equal_range(k);
        if (range.first != range.second)
        {
            auto i = range.first;
            cout << i->second;
            for (++i; i != range.second; i++)
                cout << ", " << i->second;
        }
        else
            cout << "-";
        cout << endl;
    }
    cout << "Active repairs: " << active_repairs.size() << endl;
    for (auto &i : active_repairs)
        cout << "   Request ID: " << i.first->get_ID() << ", Estimated time left: " << i.second << endl;
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
void Technician::add_repair(shared_ptr<Request> r)
{
    active_repairs.push_back({move(r), r->get_estimated_repair_time()});
}
bool Technician::work_on_repairs()
{
    if (active_repairs.begin() != active_repairs.end())
    {
        for (auto i = active_repairs.begin(); i != active_repairs.end(); i++)
        {
            if (i->second == i->first->get_estimated_repair_time()) // just received
                cout << "Technician " << ID << " received Request " << i->first->get_ID();
            else
            {
                workload++;
                cout << "Technician " << ID << " is working on Request " << i->first->get_ID() << ", Estimated time remaining: " << i->second;
            }
            i->second--;
            cout << endl;
        }
        //cout << endl;
        return 1;
    }
    else
        return 0;
}
vector<Appliance *> Technician::remove_finished_repairs()
{
    vector<Appliance *> finished;
    if (active_repairs.begin() != active_repairs.end())
    {
        for (auto i = active_repairs.begin(); i != active_repairs.end();)
            if (i->second == 0)
            {
                cout << "Technician " << ID << " finished Request " << i->first->get_ID() << endl;
                modify_bonus(i->first->get_cost() / 50); // 2% of cost as bonus
                finished.push_back(i->first->get_appliance());
                i = active_repairs.erase(i);
            }
            else
                i++;
        // cout << endl;
    }
    // for (auto i = finished.begin(); i != finished.end(); i++)
    //(*i)->print_appliance();
    return finished;
}