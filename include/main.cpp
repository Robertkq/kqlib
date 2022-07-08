#include "kqlib.h"
#include <iostream>

int main()
{
    std::cout << kq::format("Test{1}{1}", 18, 19);
    

    return 0;
}