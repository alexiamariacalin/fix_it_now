#include "ReadWrite.h"
static Service &service = Service::get();
time_t present = time(NULL);
static struct tm now = *localtime(&present);
unique_ptr<Employee> read_employee_from_file(string e)
{
    string type, name, surname, ed, CNP, hometown;
    char aux;
    int day, month, year;
    stringstream in(e);
    getline(in, type, ',');
    getline(in, name, ',');
    getline(in, surname, ',');
    getline(in, CNP, ',');
    in >> day >> aux >> month >> aux >> year;
    in.ignore(1, ',');
    getline(in, hometown, ',');
    if (type == "Supervisor")
        return (make_unique<Supervisor>(name, surname, CNP, day, month, year, hometown));

    else if (type == "Receptionist")
        return (make_unique<Receptionist>(name, surname, CNP, day, month, year, hometown));
    else if (type == "Technician")
    {
        multimap<string, string> skills;
        for (int i = 0; i < 3; i++)
        {
            string list, brand;
            getline(in, type, '(');
            getline(in, list, ')');
            stringstream ss(list);
            while (getline(ss, brand, ','))
                skills.insert({type, brand});
            in.ignore(1, ';');
        }
        return (make_unique<Technician>(name, surname, CNP, day, month, year, hometown, skills));
    }
    return nullptr;
}
unique_ptr<Appliance> read_appliance_from_file(string a)
{
    string type, brand, model;
    int year, price;
    stringstream ss(a);
    getline(ss, type, ',');
    getline(ss, brand, ',');
    getline(ss, model, ',');
    ss >> year;
    ss.ignore(1, ',');
    ss >> price;
    ss.ignore(1, ',');
    if (type == "Fridge")
    {
        string specification;
        getline(ss, specification, ',');
        bool freezer = 1;
        if (specification == "No")
            freezer = 0;
        return make_unique<Fridge>(type, brand, model, year, price, freezer);
    }
    else if (type == "TV")
    {
        int size;
        ss >> size;
        return make_unique<TV>(type, brand, model, year, price, size);
    }
    else if (type == "Washing Machine")
    {
        int capacity;
        ss >> capacity;
        return make_unique<WashingMachine>(type, brand, model, year, price, capacity);
    }
    return nullptr;
}
void read_employees_from_file(const string &file)
{
    ifstream input(file);
    if (input.fail())
    {
        cout << "Could not open file: " << file << endl;
        exit(1);
    }
    string line;
    int count = 1;
    getline(input, line);
    while (!input.eof())
    {
        count++;
        getline(input, line);
        try
        {
            service.add_employee(read_employee_from_file(line));
        }
        catch (const invalid_argument &e)
        {
            cout << "Error on line " << count << ": " << "Invalid employee data: " << e.what() << endl
                 << endl;
        }
    }
    input.close();
}
void read_appliances_from_file(const string &file)
{
    ifstream input(file);
    if (input.fail())
    {
        cout << "Could not open file: " << file << endl;
        exit(1);
    }
    string line;
    getline(input, line);
    while (!input.eof())
    {
        getline(input, line);
        service.add_appliance(read_appliance_from_file(line));
    }
    input.close();
}
shared_ptr<Request> read_request_from_file(string r)
{
    string appliance;
    int day, month, year, hour, minute, second, complexity_level;
    char aux;
    stringstream in(r);
    getline(in, appliance, ';');
    in >> day >> aux >> month >> aux >> year >> hour >> aux >> minute >> aux >> second >> aux;
    in >> complexity_level;
    return make_shared<Request>(read_appliance_from_file(appliance), day, month, year, hour, minute, second, complexity_level);
}
void read_requests_from_file(const string &file)
{
    ifstream input(file);
    if (input.fail())
    {
        cout << "Could not open file: " << file << endl;
        exit(1);
    }
    string line;
    int count = 1;
    getline(input, line);
    while (!input.eof())
    {
        count++;
        getline(input, line);
        try
        {
            shared_ptr<Request> r = read_request_from_file(line);
            service.add_request(r);
            try
            {
                auto i = service.find_appliance(*r->get_appliance());
                service.add_valid_request(r);
                dynamic_cast<Receptionist *>(service.get_receptionist()->get())->add_request_ID(r->get_ID());
            }
            catch (string error) // appliance not found
            {
                service.add_unrepairable_appliance(r->get_appliance()->get_type(), r->get_appliance()->get_brand(), r->get_appliance()->get_model());
            }
        }
        catch (const invalid_argument &e)
        {
            cout << "Error on line " << count << ": " << e.what() << endl
                 << endl;
        }
    }
    input.close();
}
void print_employee_in_file(ofstream &file, Employee *e)
{
    file << e->get_type() << "," << e->get_name() << "," << e->get_surname() << "," << e->get_CNP() << ",";
    char output[50];
    struct tm aux = e->get_employment_date();
    strftime(output, sizeof(output), "%d-%m-%Y", &aux);
    file << output;
    file << "," << e->get_hometown();
    file << "," << e->salary();
    if (e->get_type() == "Technician")
    {
        file << ",";
        vector<string> v = {"Fridge", "TV", "Washing Machine"};
        Technician *t = dynamic_cast<Technician *>(e);
        for (auto k : v)
        {
            multimap<string, string> skills = t->get_skills();
            auto range = skills.equal_range(k);
            if (range.first != range.second)
            {
                auto i = range.first;
                file << k << "(";
                file << i->second;
                for (++i; i != range.second; i++)
                    file << "," << i->second;
                file << ")";
                if (k != "Washing Machine")
                    file << ";";
            }
        }
    }
}
unique_ptr<Employee> read_employee_from_menu()
{
    string type, name, surname, CNP, hometown;
    char aux;
    int day, month, year;
    cout << "Enter employee information:" << endl;
    cout << "Type (\"Receptionist\", \"Supervisor\" or \"Technician\"): ";
    cin >> type;
    if (!(type == "Receptionist" or type == "Supervisor" or type == "Technician"))
        throw invalid_argument("Invalid employee type");
    cout
        << "Name: ";
    cin >> name;
    if (name.size() < 3)
        throw invalid_argument("Name too short");
    if (name.size() > 30)
        throw invalid_argument("Name too long");

    cout << "Surname: ";
    cin >> surname;
    if (surname.size() < 3)
        throw invalid_argument("Surname too short");
    if (surname.size() > 30)
        throw invalid_argument("Surname too long");

    cout << "CNP: ";
    cin >> CNP;
    if (validate_CNP(CNP) == 0)
        throw invalid_argument("Invalid CNP");
    if (age(CNP) < 16)
        throw invalid_argument("Must be at least 16 years old to be employed");

    cout << "Employment date (DD-MM-YYYY): ";
    cin >> day >> aux >> month >> aux >> year;
    if (validate_date(day, month, year, 0, 0, 0) == 0)
        throw invalid_argument("Invalid date");
    if (type == "Supervisor")
    {
        return make_unique<Supervisor>(name, surname, CNP, day, month, year, hometown);
        // auto s = make_unique<Supervisor>(name, surname, CNP, day, month, year, hometown);
        // service.add_employee(move(s));
    }
    else if (type == "Receptionist")
    {
        return make_unique<Receptionist>(name, surname, CNP, day, month, year, hometown);
        // auto r = make_unique<Receptionist>(name, surname, CNP, day, month, year, hometown);
        // service.add_employee(move(r));
    }
    else if (type == "Technician")
    {
        multimap<string, string> skills;
        vector<string> appliances = {"Fridge", "TV", "Washing Machine"};
        cout << "Brands of appliances able to repair (\"Brand1,Brand2,...\" or \"-\"):" << endl;
        for (int i = 0; i < 3; i++)
        {
            string list, brand;
            cout << appliances[i] << ": ";
            cin >> list;
            stringstream ss(list);
            while (getline(ss, brand, ','))
                if (brand != "-")
                    skills.insert({appliances[i], brand});
        }
        return make_unique<Technician>(name, surname, CNP, day, month, year, hometown, skills);
        // auto t = make_unique<Technician>(name, surname, CNP, day, month, year, hometown, skills);
        // service.add_employee(move(t));
    }
    return nullptr;
}
unique_ptr<Appliance> read_appliance_from_menu()
{
    string type, brand, model;
    int year, price;
    cout << "Enter appliance information:" << endl;
    cout << "Type (\"Fridge\", \"TV\" or \"Washing Machine\"): ";
    getline(cin, type); // clean the buffer
    getline(cin, type);
    if (type != "Fridge" and type != "TV" and type != "Washing Machine")
        throw invalid_argument("Invalid appliance type");
    cout << "Brand: ";
    cin >> brand;
    cout << "Model: ";
    cin >> model;
    cout << "Manufacture year (YYYY): ";
    cin >> year;
    if (year > now.tm_year + 1900 or year < 1900)
        throw invalid_argument("Invalid manufacture year");
    cout << "Catalog price: ";
    cin >> price;
    if (type == "Fridge")
    {
        string freezer;
        cout << "Freezer (\"Yes\" or \"No\"): ";
        cin >> freezer;
        if (freezer != "Yes" and freezer != "No")
            throw invalid_argument("Invalid freezer specification");
        return make_unique<Fridge>(type, brand, model, year, price, (freezer == "Yes") ? 1 : 0);
        // auto f = make_unique<Fridge>(type, brand, model, year, price, (freezer == "Yes") ? 1 : 0);
        // service.add_appliance(move(f));
    }
    else if (type == "TV")
    {
        int size;
        cout << "Size: ";
        cin >> size;
        return make_unique<TV>(type, brand, model, year, price, size);
        // auto t = make_unique<TV>(type, brand, model, year, price, size);
        // service.add_appliance(move(t));
    }
    else if (type == "Washing Machine")
    {
        int capacity;
        cout << "Capacity: ";
        cin >> capacity;
        return make_unique<WashingMachine>(type, brand, model, year, price, capacity);
        // auto w = make_unique<WashingMachine>(type, brand, model, year, price, capacity);
        // service.add_appliance(move(w));
    }
    return nullptr;
}