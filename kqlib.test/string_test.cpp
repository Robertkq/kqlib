#include "catch.hpp"
#include "..\include\kqlib\string.h"
#include "..\include\kqlib\algorithm.h"

using namespace kq;

TEST_CASE("string constructors")
{
    SECTION("string default constructor")
    {
        string str;
        REQUIRE(str.size() == 0);
        REQUIRE(str.capacity() == 0);
        REQUIRE(str.begin() == str.end());
        REQUIRE(str == "");
    }

    SECTION("string copy constructor")
    {
        string aux("12345");
        string str(aux);
        REQUIRE(str.size() == 5);
        REQUIRE(str.capacity() >= 5);
        REQUIRE(str == "12345");
    }

    SECTION("string move constructor")
    {
        string aux("12345");
        string str(std::move(aux));
        REQUIRE(aux.size() == 0);
        REQUIRE(aux == "");
        REQUIRE(str.size() == 5);
        REQUIRE(str.capacity() >= 5);
        REQUIRE(str == "12345");
    }

    SECTION("string amount constructor")
    {
        string str("1234567", 5);
        REQUIRE(str.size() == 5);
        REQUIRE(str.capacity() >= 5);
        REQUIRE(str == "12345");
    }

    SECTION("string amount & pos constructor")
    {
        string str("0123456", 1, 5);
        REQUIRE(str.size() == 5);
        REQUIRE(str.capacity() >= 5);
        REQUIRE(str == "12345");
    }

    SECTION("string assign constructor")
    {
        string str('b', 5);
        REQUIRE(str.size() == 5);
        REQUIRE(str.capacity() >= 5);
        REQUIRE(str == "bbbbb");
    }

    SECTION("string iterator constructor")
    {
        string aux("0123456");
        string str(aux.begin() + 1, aux.end() - 1);
        REQUIRE(str.size() == 5);
        REQUIRE(str.capacity() >= 5);
        REQUIRE(str == "12345");
    }
}