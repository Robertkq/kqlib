#include "catch.hpp"
#include "..\include\kqlib\deque.h"
#include "..\include\kqlib\algorithm.h"

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

    SECTION("deque initializer_list asignment")
    {
        deque<int> dq;
        dq = { 1,2,3,4,5 };
        REQUIRE(dq.size() == 5);
        REQUIRE(dq.capacity() >= 5);
        auto inc = 1;
        for (auto& e : dq)
            REQUIRE(e == inc++);
    }
}

TEST_CASE("inserting in deque", "[deque]")
{
    deque<int> dq;

    SECTION("push_back")
    {
        REQUIRE(dq.size() == 0);
        REQUIRE(dq.capacity() == 0);
        dq.push_back(1);
        dq.push_back(2);
        dq.push_back(3);
        dq.push_back(4);
        dq.push_back(5);
        dq.push_back(6);
        dq.push_back(7);
        dq.push_back(8);
        dq.push_back(9);
        REQUIRE(dq.size() == 9);
        REQUIRE(dq.capacity() >= 9);
        auto inc = 1;
        for (auto& e : dq)
            REQUIRE(e == inc++);
    }

    SECTION("push_front")
    {
        REQUIRE(dq.size() == 0);
        REQUIRE(dq.capacity() == 0);
        dq.push_front(1);
        dq.push_front(2);
        dq.push_front(3);
        dq.push_front(4);
        dq.push_front(5);
        dq.push_front(6);
        dq.push_front(7);
        dq.push_front(8);
        dq.push_front(9);
        REQUIRE(dq.size() == 9);
        REQUIRE(dq.capacity() >= 9);
        auto inc = 9;
        for (auto& e : dq)
            REQUIRE(e == inc--);
    }

    SECTION("emplace_back")
    {
        REQUIRE(dq.size() == 0);
        REQUIRE(dq.capacity() == 0);
        dq.emplace_back(1);
        dq.emplace_back(2);
        dq.emplace_back(3);
        dq.emplace_back(4);
        dq.emplace_back(5);
        dq.emplace_back(6);
        dq.emplace_back(7);
        dq.emplace_back(8);
        dq.emplace_back(9);
        REQUIRE(dq.size() == 9);
        REQUIRE(dq.capacity() >= 9);
        auto inc = 1;
        for (auto& e : dq)
            REQUIRE(e == inc++);
    }

    SECTION("emplace_front")
    {
        REQUIRE(dq.size() == 0);
        REQUIRE(dq.capacity() == 0);
        dq.emplace_front(1);
        dq.emplace_front(2);
        dq.emplace_front(3);
        dq.emplace_front(4);
        dq.emplace_front(5);
        dq.emplace_front(6);
        dq.emplace_front(7);
        dq.emplace_front(8);
        dq.emplace_front(9);
        REQUIRE(dq.size() == 9);
        REQUIRE(dq.capacity() >= 9);
        auto inc = 9;
        for (auto& e : dq)
            REQUIRE(e == inc--);
    }

    SECTION("push/emplace front/back")
    {
        dq.push_back(10);
        dq.push_back(11);
        dq.push_back(12);
        dq.push_front(9);
        dq.push_front(8);
        dq.emplace_back(13);
        dq.emplace_front(7);
        dq.emplace_front(6);
        dq.emplace_front(5);
        dq.emplace_front(4);
        dq.push_front(3);
        dq.push_front(2);
        dq.push_front(1);

        REQUIRE(dq.size() == 13);
        REQUIRE(dq.capacity() >= 13);
        auto inc = 1;
        for (auto& e : dq)
            REQUIRE(e == inc++);
    }
    //FIXME: add insert/emplace tests
}

TEST_CASE("erasing from deque", "[deque]")
{
    deque<int> dq{ 7, 3, 2, 5, 10, 9, 1, 4, 6, 8 };
    for (auto i = 1; i <= 10; ++i)
    {
        auto size = dq.size();
        dq.erase(find(dq.begin(), dq.end(), i));
        REQUIRE(dq.size() == size - 1);
        REQUIRE(find(dq.begin(), dq.end(), i) == dq.end());
    }
    REQUIRE(dq.size() == 0);
}