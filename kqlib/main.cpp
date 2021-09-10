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
	vector<int> v2(v.begin(), v.end());
	vector<int> v3;
	v3.assign(v2.begin(), v2.end());

	print(v);
	print(v2);
	print(v3);

	return 0;
}