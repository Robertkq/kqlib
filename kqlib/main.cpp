#include "kqlib.h"
#include <iostream>


int main()
{
    kq::vector<int> A({1,2,3,4,5,6});
    kq::vector<int> a(A.begin() + 1, A.end() - 1 );
    for (auto& e : a)
    {
        std::cout << e << " ";
    }
    std::cout << "\n";
    kq::list<int> B({ 1,2,3,4,5,6 });
    kq::list<int> b(++B.begin(), --B.end());
    for (auto& e : b)
    {
        std::cout << e << " ";
    }
    std::cout << "\n";
    kq::deque<int> C({ 1,2,3,4,5,6 });
    kq::deque<int> c(C.begin() + 1, C.end() - 1);
    for (auto& e : c)
    {
        std::cout << e << " ";
    }
    std::cout << "\n";
}