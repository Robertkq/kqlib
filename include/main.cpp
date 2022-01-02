#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v({ 1,2,3 });
    for (auto& e : v)
    {
        std::cout << e << " ";
    }
    v.at(4);
    std::cout << "test";
    return 0;
}