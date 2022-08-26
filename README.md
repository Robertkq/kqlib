This library is my take at recreating fundamental data structures and functions to help modify them as we like, I have tried to keep everything as similar to std as I could.

Minimum C++11.

*Special thanks to @PetrFlajsingr for helping with logic, design and solution clarifications.

# The main kqlib.h header includes:

1. kqlib\algorithm.h
2. kqlib\deque.h
3. kqlib\format.h
4. kqlib\linkedlist.h
5. kqlib\other.h
6. kqlib\pair.h
7. kqlib\single_list.h
8. kqlib\string.h
9. kqlib\vector.h
10. kqlib\unordered_map.h

# Sample
```cpp
#include <iostream>
#include "kqlib.h"

struct Person
{
    Person(const kq::string& n, int a) : name(n), age(a) {}
    kq::string name;
    int age;
};

bool name_compare(const Person& lhs, const Person& rhs) {
    return lhs.name < rhs.name;
}

auto age_compare = [](const Person& lhs, const Person& rhs) { return lhs.age < rhs.age; };

template<typename Container>
void print(const Container& cont) {
    for (const auto& person : cont) {
        std::cout << kq::format("{0:l10} is {1:r4} years old. [ {2:c10} ]\n", person.name, person.age, rand());
    } std::cout << '\n';
}

int main()
{
    kq::vector<Person> Persons{ Person{"Zoro", 18}, Person{"Robert", 19}, Person{"Lain", 20}, Person{"Daniel", 17} };

    kq::sort(Persons.begin(), Persons.end(), name_compare);
    print(Persons);
    kq::sort(Persons.begin(), Persons.end(), age_compare);
    print(Persons);

    std::cout << kq::format( "There are {} {}",
        kq::count_if(Persons.begin(), Persons.end(), [](const Person& person) { return person.age >= 18; }),
        "persons over 18 years old\n");

    return 0;
}
```
