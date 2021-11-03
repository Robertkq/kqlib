#include "kqlib.h"
#include <iostream>

using namespace kq;

int main()
{
	vector<int> v;

	v.emplace(v.begin(), 1);
	v.emplace(v.begin(), 2);
	v.emplace(v.begin(), 3);

	for (auto e : v)
		std::cout << e << " ";
	std::cout << "\n";

	v.emplace(v.begin() + 1, 4);

	for (auto e : v)
		std::cout << e << " ";
	std::cout << "\n";



	return 0;
}



/*
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
		std::cout << element.name << " " << element.age << "\n";
	}
	std::cout << "\n";
}

struct Person
{
	Person() : name("Unknown"), age(0) {}
	Person(std::string N, size_t A) : name(N), age(A) {}
	bool operator==(const Person& other) const
	{
		if (age != other.age)
		{
			return false;
		}
		else
		{
			return name != other.name;
		}
	}
	std::string name;
	size_t age;
};

int main()
{

	vector<Person> v;

	v = { Person("Robert", 18), Person("Alexandra", 19), Person("Cristian", 20),
		Person("Andrei", 21), Person("Daniel", 22) };

	print(v);

	sort(v.begin(), v.end(), [](const Person& lhs, const Person& rhs) { return lhs.name < rhs.name; });

	print(v);

	sort(v.begin(), v.end(), [](const Person& lhs, const Person& rhs) { return lhs.age < rhs.age; });

	print(v);

	return 0;
}
*/