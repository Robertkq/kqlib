#include "catch.hpp"
#include  "../include/kqlib.h"

using namespace kq;

TEST_CASE("vector constructors", "[vector]")
{
    SECTION("vector default constructor")
    {
        vector<int> vec;
        REQUIRE(vec.size() == 0);
        REQUIRE(vec.capacity() == 0);
        REQUIRE(vec.begin() == vec.end());
    }

    SECTION("vector copy constructor")
    {
        vector<int> aux{ 1,2,3,4,5 };
        vector<int> vec(aux);
        REQUIRE(vec.size() == aux.size());
        for (auto i = 0; i < vec.size(); ++i)
            REQUIRE(vec[i] == aux[i]);
    }

    SECTION("vector move constructor")
    {
        vector<int> aux{ 1,2,3,4,5 };
        vector<int> vec(std::move(aux));
        REQUIRE(vec.size() == 5);
        REQUIRE(aux.size() == 0);
        auto inc = 1;
        for (auto i = 0; i < vec.size(); ++i)
            REQUIRE(vec[i] == inc++);
    }

    SECTION("vector copy asignment")
    {
        vector<int> aux{ 1,2,3,4,5 };
        vector<int> vec;
        vec = aux;
        REQUIRE(vec.size() == aux.size());
        for (auto i = 0; i < vec.size(); ++i)
            REQUIRE(vec[i] == aux[i]);
    }

    SECTION("vector move asignment")
    {
        vector<int> aux{ 1,2,3,4,5 };
        vector<int> vec;
        vec = std::move(aux);
        REQUIRE(vec.size() == 5);
        REQUIRE(aux.size() == 0);
        auto inc = 1;
        for (auto i = 0; i < vec.size(); ++i)
            REQUIRE(vec[i] == inc++);
    }

    SECTION("vector iterator constructor")
    {
        vector<int> aux{ 1,2,3,4,5 };
        vector<int> vec(aux.begin() +1, aux.end()-1);
        REQUIRE(vec.size() == 3);
        auto inc = 2;
        for (auto i = 0; i < vec.size(); ++i)
            REQUIRE(vec[i] == inc++);
    }

    SECTION("vector initializer_list constructor")
    {
        vector<int> vec{ 1,2,3,4,5 };
        REQUIRE(vec.size() == 5);
        REQUIRE(vec.capacity() == 5);
        auto inc = 1;
        for (auto i = 0; i < vec.size(); ++i)
            REQUIRE(vec[i] == inc++);
    }

    SECTION("vector assign constructor")
    {
        vector<int> vec(3, 10);
        REQUIRE(vec.size() == 3);
        REQUIRE(vec.capacity() == 3);
        for (auto i = 0; i < vec.size(); ++i)
            REQUIRE(vec[i] == 10);
    }

    SECTION("vector size constructor")
    {
        vector<int> vec(5);
        REQUIRE(vec.size() == 5);
        REQUIRE(vec.capacity() == 5);
        for (auto i = 0; i < vec.size(); ++i)
            REQUIRE(vec[i] == 0);
    }

    SECTION("vector initializer_list asignment")
    {
        vector<int> vec;
        vec = { 1,2,3,4,5 };
        REQUIRE(vec.size() == 5);
        REQUIRE(vec.capacity() == 5);
        auto inc = 1;
        for (auto i = 0; i < vec.size(); ++i)
            REQUIRE(vec[i] == inc++);
    }
}

TEST_CASE("inserting in a vector", "[vector]")
{
    kq::vector<int> vec;
    
    SECTION("push_back vector")
    {
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        REQUIRE(vec.size() == 3);
        auto inc = 1;
        for (auto& e : vec)
            REQUIRE(e == inc++);
    }

    SECTION("insert vector")
    {
        vec = { 2, 4, 5 };
        vec.insert(vec.begin(), 1);
        vec.insert(vec.end(), 6);
        vec.insert(vec.begin() + 2, 3);
        REQUIRE(vec.size() == 6);
        REQUIRE(vec.capacity() >= 6);
        auto inc = 1;
        for (auto& e : vec)
            REQUIRE(e == inc++);
    }

    SECTION("emplace_back vector")
    {
        vec.emplace_back(1);
        vec.emplace_back(2);
        vec.emplace_back(3);
        REQUIRE(vec.size() == 3);
        auto inc = 1;
        for (auto& e : vec)
            REQUIRE(e == inc++);
    }

    SECTION("emplace vector")
    {
        vec = { 2, 4, 5 };
        vec.emplace(vec.begin(), 1);
        vec.emplace(vec.end(), 6);
        vec.emplace(vec.begin() + 2, 3);
        REQUIRE(vec.size() == 6);
        REQUIRE(vec.capacity() >= 6);
        auto inc = 1;
        for (auto& e : vec)
            REQUIRE(e == inc++);
    }
}

TEST_CASE("erasing from vector", "[vector]")
{
    vector<int> v{ 7, 3, 2, 5, 10, 9, 1, 4, 6, 8 };
    for (auto i = 1; i <= 10; ++i)
    {
        auto size = v.size();
        v.erase(find(v.begin(), v.end(), i));
        REQUIRE(v.size() == size - 1);
        REQUIRE(find(v.begin(), v.end(), i) == v.end());
    }
    REQUIRE(v.size() == 0);
}

TEST_CASE("swap vectors", "[vector]")
{
    vector<int> v1{ 1,2,3 };
    vector<int> v2{ 4,5,6,7 };

    SECTION("kq::swap")
    {
        swap(v1, v2);
        REQUIRE(v1.size() == 4);
        REQUIRE(v2.size() == 3);
        auto inc = 1;
        for (auto& e : v2)
            REQUIRE(e == inc++);
        for (auto& e : v1)
            REQUIRE(e == inc++);
    }

    SECTION("std::swap")
    {
        std::swap(v1, v2);
        REQUIRE(v1.size() == 4);
        REQUIRE(v2.size() == 3);
        auto inc = 1;
        for (auto& e : v2)
            REQUIRE(e == inc++);
        for (auto& e : v1)
            REQUIRE(e == inc++);
    }

    SECTION("vector::swap")
    {
        v1.swap(v2);
        REQUIRE(v1.size() == 4);
        REQUIRE(v2.size() == 3);
        auto inc = 1;
        for (auto& e : v2)
            REQUIRE(e == inc++);
        for (auto& e : v1)
            REQUIRE(e == inc++);
    }

}