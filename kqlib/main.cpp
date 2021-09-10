#include "kqlib.h"
#include "kqalgorithm.h"
#include <chrono>
#include <vector>
#include <iostream>
using namespace kq;

template<typename container>
void print(container& cont)
{
	for (auto& element : cont)
	{
		std::cout << element << " ";
	}
	std::cout << "\n";
}


int main()
{
	vector<int> v;

	v = { 1,2,3 };
	v.push_back(4);

	sort(v.begin(), v.end());

	print(v);

	return 0;
}