#include "catch.hpp"
#include "..\include\kqlib\string.h"
#include "..\include\kqlib\algorithm.h"

using namespace kq;

TEST_CASE("string constructors", "[string]")
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
        string str(5, 'b');
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

TEST_CASE("erasing in string", "[string]")
{
    string str;

    SECTION("erase(char)")
    {
        str = "0123456";
        str.erase(find(str.begin(), str.end(), '0'));
        str.erase(find(str.begin(), str.end(), '2'));
        str.erase(find(str.begin(), str.end(), '4'));
        str.erase(find(str.begin(), str.end(), '6'));

        REQUIRE(str == "135");
        REQUIRE(str.size() == 3);
        REQUIRE(str.capacity() >= 3);
    }

    SECTION("erase(basic_string)")
    {
        str = "I want apples";
        str.erase("apples");
        REQUIRE(str == "I want ");
        REQUIRE(str.size() == 7);
        REQUIRE(str.capacity() >= 7);
    }
}

TEST_CASE("swap strings", "[string]")
{
    string s1{ "abc" };
    string s2{ "defg"};

    SECTION("kq::swap")
    {
        swap(s1, s2);
        REQUIRE(s1.size() == 4);
        REQUIRE(s2.size() == 3);
        REQUIRE(s1 == "defg");
        REQUIRE(s2 == "abc");
    }

    SECTION("std::swap")
    {
        std::swap(s1, s2);
        REQUIRE(s1.size() == 4);
        REQUIRE(s2.size() == 3);
        REQUIRE(s1 == "defg");
        REQUIRE(s2 == "abc");
    }

    SECTION("string::swap")
    {
        s1.swap(s2);
        REQUIRE(s1.size() == 4);
        REQUIRE(s2.size() == 3);
        REQUIRE(s1 == "defg");
        REQUIRE(s2 == "abc");
    }
}

TEST_CASE("resizing & reserving string", "[string]")
{
    string str;

    SECTION("reserving higher")
    {
        str.reserve(10);
        str = "Testing";
        REQUIRE(str.capacity() >= 10);
        REQUIRE(str.size() == 7);
    }

    SECTION("reserving lower")
    {
        str = "Testing";
        auto cap = str.capacity();
        str.reserve(5);
        REQUIRE(cap == str.capacity());
    }

    SECTION("resizing")
    {
        str = "0123456789";
        str.resize(5);
        
        REQUIRE(str == "01234");
        REQUIRE(str.size() == 5);
        REQUIRE(str.capacity() >= 5);

        str.resize(10, '5');

        REQUIRE(str == "0123455555");
        REQUIRE(str.size() == 10);
        REQUIRE(str.capacity() >= 10);

        auto cap = str.capacity();

        str.resize(0);

        REQUIRE(str == "");
        REQUIRE(str.size() == 0);
        REQUIRE(str.capacity() == cap);
    }
}

TEST_CASE("lexicographical comparasions & operator+/+=", "[string]")
{
    std::string s1, s2;

    SECTION("same length comparasion")
    {
        s1 = "abc";
        s2 = "abd";
        REQUIRE(s1 < s2);
        REQUIRE(s2 > s1);
        REQUIRE(s1 <= s2);
        REQUIRE(s2 >= s1);
        REQUIRE(!(s1 == s2));
        REQUIRE(s1 != s2);
    }

    SECTION("different lengths comparasion")
    {
        s1 = "abcdef";
        s2 = "abc";
        REQUIRE(s2 < s1);
        REQUIRE(s1 > s2);
        REQUIRE(s2 <= s1);
        REQUIRE(s1 >= s2);
        REQUIRE(s1 != s2);
        REQUIRE(!(s1 == s2));
    }

    SECTION("adding sufixes (+)")
    {
        s1 = "My name is";
        s2 = "Robert";
        s1 = s1 + " ";
        s1 = s1 + s2;
        s1 = s1 + '!';
        REQUIRE(s1 == "My name is Robert!");
        
    }

    SECTION("adding sufixes (+=)")
    {
        s1 = "My name is";
        s2 = "Robert";
        s1 += " ";
        s1 += s2;
        s1 += '!';
        REQUIRE(s1 == "My name is Robert!");

    }
}

TEST_CASE("substrings", "[string]")
{
    string str("This is an example.");

    REQUIRE(str.substr(str.find(str.substr(0, 4)), 4) == "This");
    REQUIRE(str.substr(str.find("is"), 2) == "is");
    REQUIRE(str.substr(str.find("an"), 2) == "an");
    REQUIRE(str.substr(str.find("example"), 7) == "example");
    REQUIRE(str.substr(str.find("."), 1) == ".");
    
    REQUIRE(str.substr(19, 10) == "");

}