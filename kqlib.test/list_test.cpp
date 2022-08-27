#include "catch.hpp"
#include  "../include/kqlib.h"

using namespace kq;

TEST_CASE("list constructors", "[list]")
{
    SECTION("list default constructor")
    {
        list<int> vec;
        REQUIRE(vec.size() == 0);
        REQUIRE(vec.begin() == vec.end());
    }

    
}