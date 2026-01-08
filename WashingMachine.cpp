#include "WashingMachine.h"
WashingMachine::WashingMachine(string t, string b, string m, int my, int cp, int c) : Appliance(t, b, m, my, cp), capacity(c) {}
WashingMachine::WashingMachine(const WashingMachine &wm) : Appliance(wm), capacity(wm.capacity) {}
void WashingMachine::print_appliance() const
{
    Appliance::print_appliance();
    cout << "\033[A";
    cout << "Capacity: " << capacity << " kg" << endl;
    cout << endl;
}

bool WashingMachine::operator==(const Appliance &a) const
{
    return (Appliance::operator==(a) and capacity == dynamic_cast<const WashingMachine &>(a).capacity);
}