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

    SECTION("string copy assignment")
    {
        string aux("12345");
        string str;
        str = aux;
        REQUIRE(str.size() == 5);
        REQUIRE(str.capacity() >= 5);
        REQUIRE(str == "12345");
        
    }

    SECTION("string move assignment")
    {
        string aux("12345");
        string str;
        str = std::move(aux);
        REQUIRE(str.size() == 5);
        REQUIRE(str.capacity() >= 5);
        REQUIRE(str == "12345");
        REQUIRE(aux.size() == 0);
        REQUIRE(aux == "");
    }

    SECTION("string char* assignment")
    {
        string str;
        str = "12345";
        REQUIRE(str.size() == 5);
        REQUIRE(str.capacity() >= 5);
        REQUIRE(str == "12345");
    }
}

TEST_CASE("inserting in string", "[string]")
{
    string str;

    SECTION("push_back")
    {
        str.push_back('a');
        str.push_back('b');
        str.push_back('c');
        str.push_back('d');
        str.push_back('e');

        REQUIRE(str.size() == 5);
        REQUIRE(str.capacity() >= 5);
        REQUIRE(str == "abcde");
    }

    SECTION("insert")
    {
        str.insert(str.begin(), 'e');
        str.insert(str.begin(), 'd');
        str.insert(str.begin(), 'c');
        str.insert(str.begin(), 'b');
        str.insert(str.begin(), 'a');

        REQUIRE(str.size() == 5);
        REQUIRE(str.capacity() >= 5);
        REQUIRE(str == "abcde");
    }
}