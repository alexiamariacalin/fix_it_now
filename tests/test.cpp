#include <iostream>
#include <string>
#include <stdexcept>

class Produs {
private:
    std::string nume;
    double pret;

public:
    Produs(std::string n = "", double p = 0) : nume(n), pret(p) {
        if (p < 0) throw std::invalid_argument("Pretul nu poate fi negativ!");
    }

    // Declaram operatorul ca friend pentru a accesa membrii privati
    friend std::istream& operator>>(std::istream& in, Produs& p);
    
    // Operatorul << pentru afisare (ca sa verificam rezultatul)
    friend std::ostream& operator<<(std::ostream& out, const Produs& p) {
        out << "Produs: " << p.nume << " | Pret: " << p.pret << " RON";
        return out;
    }
};

// Implementarea operatorului >>
std::istream& operator>>(std::istream& in, Produs& p) {
    std::cout << "Nume produs: ";
    in >> p.nume;
    
    std::cout << "Pret produs: ";
    double pretTemp;
    in >> pretTemp;

    // Validare imediata: daca datele sunt gresite, aruncam exceptia aici
    if (pretTemp < 0) {
        throw std::invalid_argument("Pret invalid introdus la citire!");
    }

    p.pret = pretTemp;
    return in; // Returnam fluxul pentru a permite inlantuirea (ex: cin >> p1 >> p2)
}

int main() {
    Produs tableta;

    try {
        std::cin >> tableta;
        std::cout << tableta << std::endl;
    } 
    catch (const std::invalid_argument& e) {
        std::cerr << "Eroare la introducere: " << e.what() << std::endl;
    }

    return 0;
}