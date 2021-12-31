#include <iostream>
#include "kqlib.h"


int main()
{
    kq::vector<int> v({ 1,2,3,4,5, });
    kq::vector<int> v2(v.begin() + 1, v.end() - 1);
    for (auto& e : v2)
    {
        std::cout << e << " ";
    }
    return 0;
}