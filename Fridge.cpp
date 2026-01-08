#include "Fridge.h"
Fridge::Fridge(string t, string b, string m, int my, int cp, bool f) : Appliance(t, b, m, my, cp), freezer(f) {}
Fridge::Fridge(const Fridge &f) : Appliance(f), freezer(f.freezer) {}
void Fridge::print_appliance() const
{
    Appliance::print_appliance();
    cout << "\033[A"; // go back up one line (cancels the endl)
    cout << "Freezer: ";
    if (freezer)
        cout << "Yes\n";
    else
        cout << "No\n";
    cout << endl;
}
bool Fridge::operator==(const Appliance &a) const
{
    return (Appliance::operator==(a) and freezer == dynamic_cast<const Fridge &>(a).freezer);
}