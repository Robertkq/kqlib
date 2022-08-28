#include "catch.hpp"
#include  "../include/kqlib.h"

using namespace kq;

TEST_CASE("list constructors", "[list]")
{
    SECTION("list default constructor")
    {
        list<int> l;
        REQUIRE(l.size() == 0);
        REQUIRE(l.begin() == l.end());
    }

    SECTION("list copy constructor")
    {
        list<int> aux{ 1,2,3,4,5 };
        list<int> l(aux);
        REQUIRE(l.size() == 5);
        auto inc = 1;
        for (auto& e : l)
            REQUIRE(e == inc++);
    }

    SECTION("list move constructor")
    {
        list<int> aux{ 1,2,3,4,5 };
        list<int> l(std::move(aux));
        REQUIRE(l.size() == 5);
        REQUIRE(aux.size() == 0);
        auto inc = 1;
        for (auto& e : l)
            REQUIRE(e == inc++);
    }

    SECTION("list size constructor")
    {
        list<int> l(5);
        REQUIRE(l.size() == 5);
        for (auto& e : l)
            REQUIRE(e == 0);
    }

    SECTION("list assign constructor")
    {
        list<int> l(3, 10);
        REQUIRE(l.size() == 3);
        for (auto& e : l)
            REQUIRE(e == 10);
    }

    SECTION("list initializer_list constructor")
    {
        list<int> l{ 1,2,3,4,5 };
        REQUIRE(l.size() == 5);
        auto inc = 1;
        for (auto& e : l)
            REQUIRE(e == inc++);
    }

    SECTION("list copy asignment")
    {
        list<int> aux{ 1,2,3,4,5 };
        list<int> l;
        l = aux;
        REQUIRE(l.size() == 5);
        REQUIRE(aux.size() == 5);
        auto inc = 1;
        for (auto& e : l)
            REQUIRE(e == inc++);
    }

    SECTION("list move asignment")
    {
        list<int> aux{ 1,2,3,4,5 };
        list<int> l;
        l = std::move(aux);
        REQUIRE(l.size() == 5);
        REQUIRE(aux.size() == 0);
        auto inc = 1;
        for (auto& e : l)
            REQUIRE(e == inc++);
    }
}

TEST_CASE("inserting into list", "[list]")
{
    list<int> l;

    SECTION("push_back into list")
    {
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        REQUIRE(l.size() == 3);
        auto inc = 1;
        for (auto& e : l)
            REQUIRE(e == inc++);
    }

    SECTION("push_front into list")
    {
        l.push_front(1);
        l.push_front(2);
        l.push_front(3);
        REQUIRE(l.size() == 3);
        auto inc = 3;
        for (auto& e : l)
            REQUIRE(e == inc--);
    }

    SECTION("emplace_back into list")
    {
        l.emplace_back(1);
        l.emplace_back(2);
        l.emplace_back(3);
        REQUIRE(l.size() == 3);
        auto inc = 1;
        for (auto& e : l)
            REQUIRE(e == inc++);
    }

    SECTION("emplace_front into list")
    {
        l.emplace_front(1);
        l.emplace_front(2);
        l.emplace_front(3);
        REQUIRE(l.size() == 3);
        auto inc = 3;
        for (auto& e : l)
            REQUIRE(e == inc--);
    }
}

TEST_CASE("erasing from list", "[list]")
{
    list<int> l{ 7, 3, 2, 5, 10, 9, 1, 4, 6, 8 };
    for (auto i = 1; i <= 10; ++i)
    {
        auto size = l.size();
        l.erase(find(l.begin(), l.end(), i));
        REQUIRE(l.size() == size - 1);
        REQUIRE(find(l.begin(), l.end(), i) == l.end());
    }
    REQUIRE(l.size() == 0);
}

TEST_CASE("swapping lists", "[list]")
{
    list<int> l1{ 1,2,3 };
    list<int> l2{ 4,5,6,7 };
    SECTION("kq::swap")
    {
        swap(l1, l2);
        REQUIRE(l1.size() == 4);
        REQUIRE(l2.size() == 3);
        auto inc = 1;
        for (auto& e : l2)
            REQUIRE(e == inc++);
        for (auto& e : l1)
            REQUIRE(e == inc++);
    }

    SECTION("std::swap")
    {
        std::swap(l1, l2);
        REQUIRE(l1.size() == 4);
        REQUIRE(l2.size() == 3);
        auto inc = 1;
        for (auto& e : l2)
            REQUIRE(e == inc++);
        for (auto& e : l1)
            REQUIRE(e == inc++);
    }

    SECTION("std::swap")
    {
        l1.swap(l2);
        REQUIRE(l1.size() == 4);
        REQUIRE(l2.size() == 3);
        auto inc = 1;
        for (auto& e : l2)
            REQUIRE(e == inc++);
        for (auto& e : l1)
            REQUIRE(e == inc++);
    }
}

TEST_CASE("resizing list", "[list]")
{
    list<int> l(10);
    REQUIRE(l.size() == 10);
    l.resize(15);
    REQUIRE(l.size() == 15);
    l.resize(0);
    REQUIRE(l.size() == 0);
}