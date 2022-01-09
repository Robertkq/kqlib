#include <iostream>
#include "kqlib.h"
#include <vector>

int main()
{
    kq::vector<int> v({ 1,2,3,4,5 });
    
    for (kq::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << '\n';
    for (kq::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
    {
        std::cout << *it << " ";
    }
    return 0;
}