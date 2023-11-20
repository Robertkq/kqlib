#include "catch.hpp"
#include "kqlib/compare.h"
#include "kqlib/vector.h"
#include "kqlib/algorithm.h"

using namespace kq;

TEST_CASE("basic comparing", "[compare]")
{
    SECTION("equal_to")
    {
        REQUIRE(kq::equal_to<int>{}(5, 5) == true);
        REQUIRE(kq::equal_to<int>{}(10, 5) == false);
    }

    SECTION("not_equal_to")
    {
        REQUIRE(kq::not_equal_to<int>{}(10, 5) == true);
        REQUIRE(kq::not_equal_to<int>{}(5, 5) == false);
    }

    SECTION("less")
    {
        REQUIRE(kq::less<int>{}(5, 10) == true);
        REQUIRE(kq::less<int>{}(10, 5) == false);
        REQUIRE(kq::less<int>{}(5, 5) == false);
    }

    SECTION("greater")
    {
        REQUIRE(kq::greater<int>{}(10, 5) == true);
        REQUIRE(kq::greater<int>{}(5, 10) == false);
        REQUIRE(kq::greater<int>{}(5, 5) == false);
    }

    SECTION("less_equal")
    {
        REQUIRE(kq::less_equal<int>{}(5, 10) == true);
        REQUIRE(kq::less_equal<int>{}(10, 5) == false);
        REQUIRE(kq::less_equal<int>{}(5, 5) == true);
    }

    SECTION("greater_equal")
    {
        REQUIRE(kq::greater_equal<int>{}(10, 5) == true);
        REQUIRE(kq::greater_equal<int>{}(5, 10) == false);
        REQUIRE(kq::greater_equal<int>{}(5, 5) == true);
    }
}



// implementations of test types
