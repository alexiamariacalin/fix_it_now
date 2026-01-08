#include "Request.h"
Request::Request(unique_ptr<Appliance> a, int day, int month, int year, int hour, int minute, int second, int cl) : ID(++total_requests), appliance(move(a)), complexity_level(cl)
{
    if (validate_date(day, month, year, hour, minute, second) == 0)
        throw invalid_argument("Invalid request date");
    struct tm srd{.tm_sec = second, .tm_min = minute, .tm_hour = hour, .tm_mday = day, .tm_mon = month - 1, .tm_year = year - 1900};
    mktime(&srd);
    submission_request_date = srd;

    time_t present = time(NULL);
    struct tm now = *localtime(&present);

    estimated_repair_time = (now.tm_year + 1900) - appliance->get_manufacture_year(); // !!! problem for same year manufacture
    cost = appliance->get_catalog_price() * estimated_repair_time;
}
// Request::Request(const Request &r) : ID(++total_requests), appliance(r.appliance), submission_request_date(r.submission_request_date), complexity_level(r.complexity_level), estimated_repair_time(r.estimated_repair_time), cost(r.cost) {}
Request::~Request() { --total_requests; }
void Request::print_request() const
{
    cout << "REQUEST:" << endl;
    cout << "ID: " << ID << endl;
    appliance->print_appliance();
    cout << "\033[A";
    cout << "Submission request date: ";
    
    char output[50];
    strftime(output, sizeof(output), "%d/%m/%Y %T", &submission_request_date);
    cout << output << endl;

    cout << "Complexity level: " << complexity_level << endl;
    cout << "Estimated repair time: " << estimated_repair_time << endl;
    cout << "Cost: " << cost << endl;
    cout << endl;
}