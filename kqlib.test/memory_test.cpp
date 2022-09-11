#include "catch.hpp"
#include "..\include\kqlib\memory.h"

using namespace kq;

TEST_CASE("unique_ptr constructors", "[unique_ptr]")
{
    SECTION("default constructor")
    {
        unique_ptr<int> up = make_unique<int>(100);
        REQUIRE(up);
        REQUIRE(*up == 100);
    }

    SECTION("move constructor")
    {
        unique_ptr<int> aux = make_unique<int>(50);
        unique_ptr<int> up = std::move(aux);

        REQUIRE(up);
        REQUIRE(*up == 50);
    }

    SECTION("move assignment")
    {
        unique_ptr<int> aux = make_unique<int>(50);
        unique_ptr<int> up;
        REQUIRE(!up);
        up = std::move(aux);
        REQUIRE(up);
        REQUIRE(*up == 50);
        REQUIRE(!aux);
    }

    SECTION("reseting")
    {
        unique_ptr<int> up;
        int* ptr = new int(100);

        REQUIRE(!up);
        up.reset(ptr);
        REQUIRE(up);
        REQUIRE(*up == 100);
        up.reset();
        REQUIRE(!up);
    }

    SECTION("releasing")
    {
        unique_ptr<int> up = make_unique<int>(100);
        
        REQUIRE(*(up.release()) == 100);
        REQUIRE(!up);
    }
}