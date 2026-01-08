#include "TV.h"
TV::TV(string t, string b, string m, int my, int cp, int s) : Appliance(t, b, m, my, cp), size(s) {}
TV::TV(const TV &tv) : Appliance(tv), size(tv.size) {}
void TV::print_appliance() const
{
    Appliance::print_appliance();
    cout << "\033[A";
    cout << "Size: " << size << " cm (" << fixed << setprecision(2) << (double)size / 2.54 << " in)" << endl;
    cout << endl;
}
bool TV::operator==(const Appliance &a) const
{
    return (Appliance::operator==(a) and size == dynamic_cast<const TV &>(a).size);
}