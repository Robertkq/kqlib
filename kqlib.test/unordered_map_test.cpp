#include "catch.hpp"
#include "..\include\kqlib\unordered_map.h"
#include "..\include\kqlib\algorithm.h"

using namespace kq;

TEST_CASE("unordered_map constructors")
{
    // Used std::string as the key because of the convinient hasher
    SECTION("default constructor")
    {
        unordered_map<std::string, int> map;
        REQUIRE(map.size() == 0);
        REQUIRE(map.bucket_count() == 8);
        REQUIRE(map.begin() == map.end());
    }
    //pair{<const char*, int>
    SECTION("copy constructor")
    {
        unordered_map<std::string, int> aux{ {"Covrig", 100}, {"Mozarella", 50}, {"Pizza", 25} };

        unordered_map<std::string, int> map(aux);
        REQUIRE(map.size() == 3);
        REQUIRE(map.at("Covrig") == 100);
        REQUIRE(map.at("Mozarella") == 50);
        REQUIRE(map.at("Pizza") == 25);
    }

    SECTION("move constructor")
    {
        unordered_map<std::string, int> aux{ {"Covrig", 100}, {"Mozarella", 50}, {"Pizza", 25} };

        unordered_map<std::string, int> map(std::move(aux));
        REQUIRE(map.size() == 3);
        REQUIRE(map.at("Covrig") == 100);
        REQUIRE(map.at("Mozarella") == 50);
        REQUIRE(map.at("Pizza") == 25);
        REQUIRE(aux.size() == 0);
    }

    SECTION("bucket_count constructor")
    {
        unordered_map<std::string, int> map(100);

        REQUIRE(map.size() == 0);
        REQUIRE(map.bucket_count() == 100);
    }

    SECTION("iterator constructor")
    {
        unordered_map<std::string, int> aux{ {"Covrig", 100}, {"Mozarella", 50}, {"Pizza", 25} };

        unordered_map<std::string, int> map(aux.begin(), aux.end());
        REQUIRE(map.size() == 3);
        REQUIRE(map.at("Covrig") == 100);
        REQUIRE(map.at("Mozarella") == 50);
        REQUIRE(map.at("Pizza") == 25);
    }

    SECTION("initializer_list constructor")
    {
        unordered_map<std::string, int> map{ {"Covrig", 100}, {"Mozarella", 50}, {"Pizza", 25} };
        REQUIRE(map.size() == 3);
        REQUIRE(map.at("Covrig") == 100);
        REQUIRE(map.at("Mozarella") == 50);
        REQUIRE(map.at("Pizza") == 25);
    }

    SECTION("copy assignment")
    {
        unordered_map<std::string, int> aux{ {"Covrig", 100}, {"Mozarella", 50}, {"Pizza", 25} };

        unordered_map<std::string, int> map;
        map = aux;
        REQUIRE(map.size() == 3);
        REQUIRE(map.at("Covrig") == 100);
        REQUIRE(map.at("Mozarella") == 50);
        REQUIRE(map.at("Pizza") == 25);
    }

    SECTION("move assignment")
    {
        unordered_map<std::string, int> aux{ {"Covrig", 100}, {"Mozarella", 50}, {"Pizza", 25} };

        unordered_map<std::string, int> map;
        map = std::move(aux);
        REQUIRE(map.size() == 3);
        REQUIRE(map.at("Covrig") == 100);
        REQUIRE(map.at("Mozarella") == 50);
        REQUIRE(map.at("Pizza") == 25);
        REQUIRE(aux.size() == 0);
    }
}