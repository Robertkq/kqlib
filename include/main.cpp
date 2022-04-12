#include <iostream>
#include "kqlib.h"
#include <vector>
#include <algorithm>

struct A
{
    A() : v() {}
    A(int w) : v(w) {}
    bool operator<(const A& other) const { return v < other.v; }

    int v;
};

struct Elev {
    Elev(const char* n, int v) {
        nume = n; varsta = v; 
    }
    bool operator<(const Elev& o) const {
        return varsta < o.varsta;
    }
    kq::string nume;
     int varsta;
};

void print(kq::vector<Elev>& v) {
    for (auto& e : v)
        std::cout << e.nume << " ";
    std::cout << "\n";
}
int main() {
    kq::vector<Elev> v({ Elev("Robert", 19),Elev("Andrei", 20),Elev("Darius", 18) });
    print(v);           // Robert Andrei Darius
    kq::sort(v.begin(), v.end());
    print(v);           // Darius Robert Andrei - Ordonat crescator dupa varsta
    kq::sort(v.begin(), v.end(), [](const Elev& a, const Elev& b) {
        return a.nume < b.nume;
        });
    print(v);           // Andrei Darius Robert - Ordonat crescator dupa nume
    std::cout << count_if(v.begin(), v.end(), [](const Elev& e) {
        return e.varsta > 18;
        }); // 2 - Doar 2 elevi au peste 18 ani.
    return 0;
}