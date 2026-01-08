#include "Appliance.h"
Appliance::Appliance() : type("unspecified"), brand("unspecified"), model("unspecified"), manufacture_year(0), catalog_price(0) {}
Appliance::Appliance(string t, string b, string m, int my, int cp) : type(t), brand(b), model(m), manufacture_year(my), catalog_price(cp) {}
Appliance::Appliance(const Appliance &a) : type(a.type), brand(a.brand), model(a.model), manufacture_year(a.manufacture_year), catalog_price(a.catalog_price) {}
void Appliance::print_appliance() const
{
    cout << "Type: " << type << endl;
    cout << "Brand: " << brand << endl;
    cout << "Model: " << model << endl;
    cout << "Manufacture year: " << manufacture_year << endl;
    cout << "Catalog price: " << catalog_price << endl;
    cout << endl;
}
bool Appliance::operator==(const Appliance &a) const
{
    return a.type == type && a.brand == brand && a.model == model && a.manufacture_year == manufacture_year && a.catalog_price == catalog_price;
}