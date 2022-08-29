#include "catch.hpp"
#include "..\include\kqlib\deque.h"

using namespace kq;

TEST_CASE("deque constructors", "[deque]")
{
    SECTION("deque default constructor")
    {
        deque<int> dq;
        REQUIRE(dq.size() == 0);
        REQUIRE(dq.capacity() == 0);
        REQUIRE(dq.begin() == dq.end());
    }

    SECTION("deque copy constructor")
    {
        deque<int> aux{ 1,2,3,4,5 };
        deque<int> dq(aux);
        REQUIRE(dq.size() == 5);
        REQUIRE(dq.capacity() >= 5);
        auto inc = 1;
        for (auto& e : dq)
            REQUIRE(e == inc++);
    }

    SECTION("deque move constructor")
    {
        deque<int> aux{ 1,2,3,4,5 };
        deque<int> dq(std::move(aux));
        REQUIRE(dq.size() == 5);
        REQUIRE(dq.capacity() >= 5);
        REQUIRE(aux.size() == 0);
        auto inc = 1;
        for (auto& e : dq)
            REQUIRE(e == inc++);
    }

    SECTION("deque size constructor")
    {
        deque<int> dq(5);
        REQUIRE(dq.size() == 5);
        REQUIRE(dq.capacity() >= 5);
        for (auto& e : dq)
            REQUIRE(e == 0);
    }

    SECTION("deque asign constructor")
    {
        deque<int> dq(3, 10);
        REQUIRE(dq.size() == 3);
        REQUIRE(dq.capacity() >= 3);
        for (auto& e : dq)
            REQUIRE(e == 10);
    }

    SECTION("deque initializer_list constructor")
    {
        deque<int> dq{ 1,2,3,4,5 };
        REQUIRE(dq.size() == 5);
        REQUIRE(dq.capacity() >= 5);
        auto inc = 1;
        for (auto& e : dq)
            REQUIRE(e == inc++);
    }

    SECTION("deque iterator constructor")
    {
        deque<int> aux{ 1,2,3,4,5 };
        deque<int> dq(aux.begin() + 1, aux.end() - 1);
        REQUIRE(dq.size() == 3);
        REQUIRE(dq.capacity() >= 3);
        auto inc = 2;
        for (auto& e : dq)
            REQUIRE(e == inc++);
    }

    SECTION("deque copy asignment")
    {
        deque<int> aux{ 1,2,3,4,5 };
        deque<int> dq;
        dq = aux;
        REQUIRE(dq.size() == 5);
        REQUIRE(dq.capacity() >= 5);
        auto inc = 1;
        for (auto& e : dq)
            REQUIRE(e == inc++);
    }

    SECTION("deque move asignment")
    {
        deque<int> aux{ 1,2,3,4,5 };
        deque<int> dq;
        dq = std::move(aux);
        REQUIRE(aux.size() == 0);
        REQUIRE(dq.size() == 5);
        REQUIRE(dq.capacity() >= 5);
        auto inc = 1;
        for (auto& e : dq)
            REQUIRE(e == inc++);
    }
}