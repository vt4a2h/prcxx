//
// MIT License
//
// Copyright (c) 2020-present Vitaly Fanaskov
//
// prcxx -- Yet another C++ property library
// Project home: https://github.com/vt4a2h/prcxx
//
// See LICENSE file for the further details.
//
#include "catch.hpp"

#include <string>

#include <prcxx/property.hpp>

TEST_CASE("Properties can be compared") {
    using namespace prcxx;

    SECTION("Empty properties are equal") {
        property<int> p1;
        property<int> p2;

        REQUIRE(p1 == p2);
    }

    SECTION("Non-empty properties are equal") {
        property<int> p1(1);
        property<int> p2(2);

        REQUIRE_FALSE(p1 == p2);
    }

    SECTION("The second property is greater than the first one") {
        property<int> p1(1);
        property<int> p2(2);

        REQUIRE(p2 > p1);
    }

    SECTION("The first property is less than the second one") {
        property<int> p1(1);
        property<int> p2(2);

        REQUIRE(p1 < p2);
    }

    SECTION("First and second properties are not related") {
        property<int> p1;
        property<int> p2(2);

        REQUIRE_FALSE((p1 < p2 || p1 > p2 || p1 == p2)); // NOLINT
    }
}