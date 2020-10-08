#include "catch.hpp"

#include <string>

#include <prcxx/property.hpp>

TEST_CASE("properties can be compared") {
    using namespace prcxx;

    SECTION("empty properties are equal") {
        property<int> p1;
        property<int> p2;

        REQUIRE(p1 == p2);
    }

    SECTION("equal") {
        property<int> p1(1);
        property<int> p2(2);

        REQUIRE_FALSE(p1 == p2);
    }

    SECTION("p2 is greater than p1") {
        property<int> p1(1);
        property<int> p2(2);

        REQUIRE(p2 > p1);
    }

    SECTION("p1 is less than p2") {
        property<int> p1(1);
        property<int> p2(2);

        REQUIRE(p1 < p2);
    }

    SECTION("p1 and p2 are not related") {
        property<int> p1;
        property<int> p2(2);

        REQUIRE_FALSE((p1 < p2 || p1 > p2 || p1 == p2)); // NOLINT
    }
}