#include "catch.hpp"
#include "..\include\kqlib\unordered_map.h"
#include "..\include\kqlib\algorithm.h"

using namespace kq;

TEST_CASE("unordered_map constructors", "[unordered_map]")
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

    SECTION("initializer_list assignment")
    {
        unordered_map<std::string, int> map;
        map = { {"Covrig", 100}, {"Mozarella", 50}, {"Pizza", 25} };
        REQUIRE(map.size() == 3);
        REQUIRE(map.at("Covrig") == 100);
        REQUIRE(map.at("Mozarella") == 50);
        REQUIRE(map.at("Pizza") == 25);
    }
}

TEST_CASE("inserting into unordered_map", "[unordered_map]")
{
    unordered_map<std::string, int> map;

    SECTION("insert()")
    {
        map.insert({ "Covrig", 100 });
        map.insert({ "Mozarella", 50 });
        map.insert({ "Pizza", 25 });

        //Duplicates should not be inserted
        map.insert({ "Covrig", 75 });
        map.insert({ "Mozarella", 25 });

        REQUIRE(map.size() == 3);
        REQUIRE(map.at("Covrig") == 100);
        REQUIRE(map.at("Mozarella") == 50);
        REQUIRE(map.at("Pizza") == 25);
    }

    SECTION("operator[]")
    {
        map["Covrig"] = 100;
        map["Mozarella"] = 50;
        map["Pizza"] = 25;

        //Duplicates should not be inserted
        map["Covrig"] = 75;
        map["Mozarella"] = 25;

        REQUIRE(map.size() == 3);
        REQUIRE(map.at("Covrig") == 100);
        REQUIRE(map.at("Mozarella") == 50);
        REQUIRE(map.at("Pizza") == 25);
    }

    SECTION("emplace()")
    {
        map.emplace(pair<std::string, int>{ "Covrig", 100 });
        map.emplace(pair<std::string, int>{ "Mozarella", 50 });
        map.emplace(pair<std::string, int>{ "Pizza", 25 });

        //Duplicates should not be emplaced
        map.emplace(pair<std::string, int>{ "Covrig", 75 });
        map.emplace(pair<std::string, int>{ "Mozarella", 25 });

        REQUIRE(map.size() == 3);
        REQUIRE(map.at("Covrig") == 100);
        REQUIRE(map.at("Mozarella") == 50);
        REQUIRE(map.at("Pizza") == 25);
    }
}