#include "kqlib.h"
#include <iostream>

using namespace kq;

struct test
{
    int v;
    int w;
};


int main()
{
    string s;

    s.push_back('r');
    std::cout << "String : " << s << ", size : " << s.size() << ", capacity : " << s.capacity() << "\n";
    s.push_back('o');
    std::cout << "String : " << s << ", size : " << s.size() << ", capacity : " << s.capacity() << "\n";
    s.push_back('b');
    std::cout << "String : " << s << ", size : " << s.size() << ", capacity : " << s.capacity() << "\n";
    s.push_back('e');
    std::cout << "String : " << s << ", size : " << s.size() << ", capacity : " << s.capacity() << "\n";
    s.push_back('r');
    std::cout << "String : " << s << ", size : " << s.size() << ", capacity : " << s.capacity() << "\n";
    s.push_back('t');
    std::cout << "String : " << s << ", size : " << s.size() << ", capacity : " << s.capacity() << "\n";
}