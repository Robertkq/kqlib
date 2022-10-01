#include "catch.hpp"
#include "..\include\kqlib\vector.h"

using namespace kq;

TEST_CASE("vector iterators")
{
    vector<int> vec({ 1,2,3,4,5,6,7,8,9,10 });
    SECTION("rational operations")
    {
        REQUIRE(vec.size() == vec.end() - vec.begin());
        REQUIRE(vec.begin() < vec.end());
        REQUIRE(vec.begin() <= vec.end());
        REQUIRE(vec.end() > vec.begin());
        REQUIRE(vec.end() >= vec.begin());

        REQUIRE(vec.size() == vec.rend() - vec.rbegin());
        REQUIRE(vec.rbegin() < vec.rend());
        REQUIRE(vec.rbegin() <= vec.rend());
        REQUIRE(vec.rend() > vec.rbegin());
        REQUIRE(vec.rend() >= vec.rbegin());

    }
}