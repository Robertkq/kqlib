#include "kqlib.h"
#include "kqalgorithm.h"
#include <chrono>
#include <vector>
#include <iostream>
using namespace kq;

template<typename container>
void print(container& list)
{
	for (auto& element : list)
	{
		std::cout << element << " ";
	}
	std::cout << "\n";
}


int main()
{
	vector<int> v({ 1, 6, 2002, 19, 100 });
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << "\n";
	v[0] = v[1] + 1;
	std::cout << v.front();
	vector<int> v2(v.begin(), v.end());

	return 0;
}