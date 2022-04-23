#include <iostream>
#include "kqlib.h"
#include "kqlib\format.h"


int main()
{
    kq::vector<kq::string> v({ kq::string("Daniel Vuvucescu Robert Al VII-lea"),
        kq::string("Gica Darius David Nr.1"),
        kq::string("Negru Emanuel Ioan"),
        kq::string("Dusanescu Toskana") });

    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << kq::format("Persoana {0:c50}, este top!\n", v[i]);
    }
    std::cout << "\n\n\n";
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << kq::format("Persoana {0:r50}, este top!\n", v[i]);
    }
    std::cout << "\n\n\n";
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << kq::format("Persoana {0:50}, este top!\n", v[i]);
    }

    return 0;
}