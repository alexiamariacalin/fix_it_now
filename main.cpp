#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <sstream>
#include "Service.h"
Service &service = Service::get();
using namespace std;
int Employee::ID_generator = 0;
int Request::total_requests = 0;
int main(int argc, const char *argv[])
{
    read_employees_from_file(argv[2]);
    try
    {
        bool x = service.validate_service();
    }
    catch (string error)
    {
        cout << error << endl;
        return 0;
    }

    read_appliances_from_file(argv[1]);
    // service.print_appliances();

    // service.print_employees();

    // read_requests_from_file(argv[3]);
    service.sort_requests_by_date();
    // service.print_requests();

    map<string, int> menu = {{"1a", 1},
                             {"1b", 2},
                             {"1c", 3},
                             {"1d", 4},
                             {"1e", 5},
                             {"2a", 6},
                             {"2b", 7},
                             {"2c", 8},
                             {"2d", 9},
                             {"3a", 10},
                             {"3b", 11},
                             {"3c", 12},
                             {"4a", 13},
                             {"4b", 14},
                             {"4c", 15},
                             {"0", 0},
                             {"help", -1}};
    cout << "WELCOME TO FixItNow!" << endl;
    cout << ifstream("Menu.txt").rdbuf(); // display menu from file
    bool ok = 1;
    while (ok)
    {
        string input;
        cout << "Enter \"help\" to revisit the menu or pick an action (e.g. \"1a\", \"2b\" or \"0\"): ";
        cin >> input;
        try
        {
            int option = menu.at(input);
            switch (option)
            {
            case 1: // add employee
            {
                try
                {
                    service.add_employee(read_employee_from_menu());
                }
                catch (const invalid_argument &e)
                {
                    cout << e.what() << endl
                         << "Action aborted" << endl
                         << endl;
                }
                break;
            }
            case 2: // modify employee
            {
                int id;
                string new_surname;
                cout << "Enter the ID of the employee to modify: ";
                cin >> id;
                try
                {
                    auto i = service.find_employee_by_id(id);
                    cout << "Enter the new surname: ";
                    cin >> new_surname;
                    service.modify_employee(i, new_surname);
                }
                catch (string error)
                {
                    cout << error << endl
                         << "Action aborted" << endl
                         << endl;
                }
                break;
            }
            case 3: // delete employee
            {
                int id;
                cout << "Enter the ID of the employee to delete: ";
                cin >> id;
                try
                {
                    service.delete_employee(id);
                }
                catch (string error)
                {
                    cout << error << endl
                         << "Action aborted" << endl
                         << endl;
                }
                break;
            }
            case 4: // find employee
            {
                string cnp;
                cout << "Enter CNP of the employee: ";
                cin >> cnp;
                try
                {
                    (*(service.find_employee_by_CNP(cnp)))->print_employee();
                }
                catch (string error)
                {
                    cout << error << endl
                         << "Action aborted" << endl
                         << endl;
                }
                break;
            }
            case 5: // print employees
            {
                service.print_employees();
                break;
            }
            case 6: // add appliance
            {
                try
                {
                    service.add_appliance(read_appliance_from_menu());
                }
                catch (const invalid_argument &e)
                {
                    cout << e.what() << endl
                         << "Action aborted" << endl
                         << endl;
                }
                break;
            }
            case 7: // delete appliance
            {
                try
                {
                    service.delete_appliance();
                }
                catch (string error)
                {
                    cout << error << endl
                         << "Action aborted" << endl
                         << endl;
                }
                break;
            }
            case 9: // print unrepairable appliances
            {
                service.print_unrepairable_appliances();
                break;
            }
            case 10: // read requests
            {
                read_requests_from_file(argv[3]);
                service.print_valid_requests();
                break;
            }
            case 13: // top 3 employees by salary
            {
                service.sort_employees_by_salary();
                service.top_3_employees();
                cout << "File generated successfully, check tests/top3employees.csv" << endl
                     << endl;
                break;
            }
            case -1: // help
            {
                cout << ifstream("Menu.txt").rdbuf(); // display menu from file
                break;
            }
            case 0: // exit
            {
                ok = 0;
                cout << "Service exited" << endl
                     << "Thank you for choosing FixItNow!" << endl;
                break;
            }
            }
        }
        catch (const out_of_range &e)
        {
            cout << "Invalid combination (action does not exist)" << endl;
        }
    }
    return 0;
}