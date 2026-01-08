#include "Service.h"
void Service::print_employees() const
{
    cout << "TOTAL EMPLOYEES: " << employees.size() << endl
         << endl;
    for (auto &i : employees)
        i->print_employee();
}
void Service::add_employee(unique_ptr<Employee> e)
{
    cout << e->get_type() << " added successfully" << endl
         << endl;
    employees.push_back(move(e));
}
vector<unique_ptr<Employee>>::iterator Service::find_employee_by_id(int id)
{
    for (auto i = employees.begin(); i != employees.end(); i++)
        if ((*i)->get_ID() == id)
            return i;
    throw "Employee " + to_string(id) + " does not exist";
}
vector<unique_ptr<Employee>>::iterator Service::find_employee_by_CNP(string cnp)
{
    for (auto i = employees.begin(); i != employees.end(); i++)
        if ((*i)->get_CNP() == cnp)
            return i;
    throw "Employee with CNP = " + cnp + " does not exist";
}
vector<unique_ptr<Employee>>::iterator Service::get_receptionist()
{
    for (auto i = employees.begin(); i != employees.end(); i++)
        if ((*i)->get_type() == "Receptionist")
            return i;
    //throw(string) "Receptionist not found";
}
void Service::modify_employee(vector<unique_ptr<Employee>>::iterator i, string surname) // NOT FINISHED YET
{
    (*i)->modify_surname(surname);
    cout << "Surname changed successfully" << endl
         << endl;
    return;
}
void Service::delete_employee(int id)
{
    auto i = find_employee_by_id(id); // can throw exception
    employees.erase(i);
    cout << "Employee " << id << " deleted successfully" << endl
         << endl;
}
void Service::print_appliances() const
{
    cout << "TOTAL REPAIRABLE APPLIANCES: " << appliances.size() << endl;
    for (auto &i : appliances)
        i->print_appliance();
}
void Service::add_appliance(unique_ptr<Appliance> a)
{
    cout << a->get_type() << " added successfully" << endl
         << endl;
    appliances.push_back(move(a));
}
void Service::add_unrepairable_appliance(string type, string brand, string model)
{
    // cout << "FOUND UNREPAIRABLE APPLIANCE" << endl;
    auto i = unrepairable_appliances.find({type, {brand, model}});
    if (i != unrepairable_appliances.end()) // already exists
        i->second++;
    else
        unrepairable_appliances.insert({{type, {brand, model}}, 1});
}
void Service::print_unrepairable_appliances() const
{
    cout << "TOTAL UNREPAIRABLE APPLIANCES: " << unrepairable_appliances.size() << endl
         << endl;
    vector<pair<pair<string, pair<string, string>>, int>> aux(unrepairable_appliances.begin(), unrepairable_appliances.end());
    sort(aux.begin(), aux.end(), [](const pair<pair<string, pair<string, string>>, int> &a, const pair<pair<string, pair<string, string>>, int> &b)
         { return a.second > b.second; }); // sort by number of requests in descending order
    for (auto &i : aux)
    {
        cout << "Type: " << i.first.first << endl;
        cout << "Brand: " << i.first.second.first << endl;
        cout << "Model: " << i.first.second.second << endl;
        cout << "Number of requests: " << i.second << endl;
        cout << endl;
    }
    cout << endl;
}
void Service::add_valid_request(shared_ptr<Request> r)
{
    valid_requests.push(move(r));
    // get id, add to receptionist's valid requests
}
void Service::add_invalid_request(shared_ptr<Request> r)
{
    invalid_requests.push_back(move(r));
}
void Service::add_request(shared_ptr<Request> r)
{
    cout << "Request " << r->get_ID() << " received successfully" << endl
         << endl;
    requests.push_back(move(r));
}
void Service::print_requests() const
{
    cout << "TOTAL REQUESTS: " << requests.size() << endl;
    for (auto &i : requests)
        i->print_request();
}
void Service::print_valid_requests() const
{
    cout << "TOTAL VALID REQUESTS: " << valid_requests.size() << endl;
    auto temp_priority_queue = valid_requests;
    while (!temp_priority_queue.empty())
    {
        temp_priority_queue.top()->print_request();
        temp_priority_queue.pop();
    }
}
bool Service::validate_service() const
{
    int supervisors = 0, technicians = 0, receptionists = 0;
    for (auto &i : employees)
    {
        string type = i->get_type();
        (type == "Supervisor") ? supervisors++ : supervisors;
        (type == "Technician") ? technicians++ : technicians;
        (type == "Receptionist") ? receptionists++ : receptionists;
    }
    if (!(supervisors == 1 and receptionists == 1 and technicians >= 3))
        throw(string) "Not enough employees, the service cannot operate";
    return 1;
}
void Service::sort_requests_by_date()
{
    sort(requests.begin(), requests.end(), [](const shared_ptr<Request> &r1, const shared_ptr<Request> &r2)
         { return tm_date_to_string(r1->get_submission_request_date()) < tm_date_to_string(r2->get_submission_request_date()); });
}
void Service::sort_employees_by_salary()
{
    sort(employees.begin(), employees.end(), [](const unique_ptr<Employee> &e1, const unique_ptr<Employee> &e2)
         { return e1->salary() > e2->salary(); });
}
void Service::top_3_employees() const
{
    Employee *e1 = employees[0].get();
    Employee *e2 = employees[1].get();
    Employee *e3 = employees[2].get();
    vector<Employee *> aux = {e1, e2, e3};
    sort(aux.begin(), aux.end(), [](Employee *e1, Employee *e2)
         { return e1->get_surname() <= e2->get_surname() || e1->get_name() <= e2->get_name(); });
    // aux[0]->print_employee();
    // aux[1]->print_employee();
    // aux[2]->print_employee();
    ofstream out("tests/top3employees.csv");
    out << "TYPE,NAME,SURNAME,CNP,EMPLOYMENT DATE(DD-MM-YYYY),HOMETOWN,SALARY,LIST OF APPLIANCES(FOR TECHNICIANS ONLY)" << endl;
    for (auto i = aux.begin(); i != aux.end(); i++)
    {
        print_employee_in_file(out, *i);
        out << endl;
    }
    out.close();
}
vector<unique_ptr<Appliance>>::iterator Service::find_appliance(const Appliance &a) // returns position in vector
{
    for (auto i = appliances.begin(); i != appliances.end(); i++)
        if ((*i)->get_type() == a.get_type() and (*i)->get_brand() == a.get_brand() and (*i)->get_model() == a.get_model())
            return i;
    throw(string) "Appliance not found";
}
void Service::delete_appliance()
{
    cout << "Enter appliance details to delete:" << endl;
    string type, brand, model;
    cout << "Type: ";
    getline(cin, type);
    getline(cin, type); // clean buffer
    if (!(type == "Fridge" or type == "TV" or type == "Washing Machine"))
        throw(string) "Invalid appliance type";
    cout << "Brand: ";
    cin >> brand;
    cout << "Model: ";
    cin >> model;
    auto a = unique_ptr<Appliance>();
    if (type == "Fridge")
        a = make_unique<Fridge>(type, brand, model, 0, 0, 0);
    else if (type == "TV")
        a = make_unique<TV>(type, brand, model, 0, 0, 0);
    else if (type == "Washing Machine")
        a = make_unique<WashingMachine>(type, brand, model, 0, 0, 0);
    auto i = find_appliance(*a); // can throw exception
    appliances.erase(i);
    cout << "Appliance deleted successfully" << endl
         << endl;
}