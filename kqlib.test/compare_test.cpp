#include "catch.hpp"
#include "..\include\kqlib\compare.h"
#include "..\include\kqlib\vector.h"
#include "..\include\kqlib\algorithm.h"

struct myValue {
    int value;
    myValue() : value() {}
    myValue(const myValue& other) : value(other.value) {}
    myValue(myValue&& other) noexcept : value(other.value) {}
    myValue(int v) : value(v) {}
    myValue& operator=(const myValue& other) { value = other.value; return *this; }
    myValue& operator=(myValue&& other) noexcept { value = other.value; return *this; }
};

struct only_greater : myValue
{
    only_greater(int v) : myValue(v) {};
    bool operator<(const only_greater& rhs) const = delete;
    bool operator>(const only_greater& rhs) const { return value > rhs.value; };
};

struct only_less : myValue
{
    only_less(int v) : myValue(v) {};
    bool operator<(const only_less& rhs) const { return value < rhs.value; };
    bool operator>(const only_less& rhs) const = delete;
};

struct only_equal : myValue
{
    only_equal(int v) : myValue(v) {};
    bool operator==(const only_equal& rhs) const { return value == rhs.value; }
    bool operator!=(const only_equal& rhs) const = delete;
};

struct only_not_equal : myValue
{
    only_not_equal(int v) : myValue(v) {};
    bool operator==(const only_not_equal& rhs) const = delete;
    bool operator!=(const only_not_equal& rhs) const { return value != rhs.value; }
};



TEST_CASE("basic comparing", "[compare]")
{
    SECTION("only_greater")
    {
        only_greater five{ 5 };
        only_greater four{ 4 };

        // <
        REQUIRE(kq::less<only_greater>{}(five, four) == false);
        REQUIRE(kq::less<only_greater>{}(four, five) == true);

        // >
        REQUIRE(kq::greater<only_greater>{}(five, four) == true);
        REQUIRE(kq::greater<only_greater>{}(four, five) == false);

        // <=
        REQUIRE(kq::less_equal<only_greater>{}(five, four) == false);
        REQUIRE(kq::less_equal<only_greater>{}(four, five) == true);

        std::less_equal<int>;

        // >=
        REQUIRE(kq::greater_equal<only_greater>{}(five, four) == true);
        REQUIRE(kq::greater_equal<only_greater>{}(four, five) == false);
    }

    SECTION("only_less")
    {
        only_less five{ 5 };
        only_less four{ 4 };

        // <
        REQUIRE(kq::less<only_less>{}(five, four) == false);
        REQUIRE(kq::less<only_less>{}(four, five) == true);

        // >
        REQUIRE(kq::greater<only_less>{}(five, four) == true);
        REQUIRE(kq::greater<only_less>{}(four, five) == false);

        // <=
        REQUIRE(kq::less_equal<only_less>{}(five, four) == false);
        REQUIRE(kq::less_equal<only_less>{}(four, five) == true);

        // >=
        REQUIRE(kq::greater_equal<only_less>{}(five, four) == true);
        REQUIRE(kq::greater_equal<only_less>{}(four, five) == false);
    }
}



// implementations of test types
