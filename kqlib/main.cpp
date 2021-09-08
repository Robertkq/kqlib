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
	{
		auto start = std::chrono::system_clock::now();


		
		size_t size = 1000000;
		while (size > 0)
		{
			std::vector<int> v({ 1,2,3,9,8,7,4,5,6 });
			v.push_back(10);
			v.push_back(11);
			v.push_back(12);
			--size;
		}

		auto end = std::chrono::system_clock::now();
		auto elapsed = end - start;
		std::cout << elapsed.count() << "\n";
	}

	{
		auto start = std::chrono::system_clock::now();


		
		size_t size = 1000000;
		while (size > 0)
		{
			kq::vector<int> v({ 1,2,3,9,8,7,4,5,6 });
			v.push_back(10);
			v.push_back(11);
			v.push_back(12);
			--size;
		}

		auto end = std::chrono::system_clock::now();
		auto elapsed = end - start;
		std::cout << elapsed.count();
	}

	return 0;
}