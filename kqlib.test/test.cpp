#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include  "../include/kqlib.h"

namespace vector
{
    TEST_CASE("vectors can be sized and resized", "[vector]") {

        kq::vector<int> v(5);

        REQUIRE(v.size() == 5);
        REQUIRE(v.capacity() >= 5);

        SECTION("reserving bigger changes capacity but not size") {
            v.reserve(10);

            REQUIRE(v.size() == 5);
            REQUIRE(v.capacity() >= 10);
        }
        SECTION("reserving smaller does not change size or capacity") {
            v.reserve(0);

            REQUIRE(v.size() == 5);
            REQUIRE(v.capacity() >= 5);
        }
    }

    TEST_CASE("vector sorting", "[vector]")
    {
        kq::vector<int> v({ 2,1,4,3,5 });
        kq::vector<int> v2({ 1,2,3,4,5 });
        kq::sort(v.begin(), v.end());
        REQUIRE(v == v2);
        v2.assign({ 5,4,3,2,1 });
        kq::sort(v.begin(), v.end(), kq::greater<int>{});
        REQUIRE(v == v2);
    }

    TEST_CASE("empty vectors", "[vector]")
    {
        kq::vector<int> v;
        REQUIRE(v.is_empty() == true);
        v.push_back(1);
        REQUIRE(v.is_empty() == false);
    }

    TEST_CASE("find, in vector", "[vector]")
    {
        kq::vector<float> v({ 1.1, 2.2, 3.3, 4.4, 5.5, 6.6 });
        REQUIRE(kq::find(v.begin() + 1, v.end() - 1, 3.3f) == v.begin() + 2);
    }

    TEST_CASE("Comparing values of Constructor with default constructor + assign", "[vector]")
    {
        kq::vector<int> v;
        v.assign({ 1, 2, 3, 4, 5 });
        kq::vector<int> v2(v);
        REQUIRE(v == v2);
        kq::vector<int> v3({ 1,2,3,4,5 });
        REQUIRE(v == v3);
        kq::vector<int> v4(v3.begin(), v3.end());
        REQUIRE(v == v4 );
        v.assign(v3.begin(), v3.end());
        REQUIRE(v == v3);
    }

    TEST_CASE("sorting vector", "[vector]")
    {
        kq::vector<int> v({ 1,2,3,4,5 });
        kq::vector<int> v2({ 3,2,4,5,1 });
        kq::sort(v2.begin(), v2.end());
        REQUIRE(v == v2);
    }

}

namespace list
{

}