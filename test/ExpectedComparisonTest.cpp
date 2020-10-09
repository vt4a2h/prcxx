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

#include <prcxx/Expected.hpp>

TEST_CASE("Expected is comparable") {
    using namespace prcxx;

    SECTION("Left is more than right") {
        Expected<int> l = 42;
        Expected<int> r = 24;

        REQUIRE(l > r);
    }

    SECTION("Right is more than left") {
        Expected<int> l = 24;
        Expected<int> r = 42;

        REQUIRE(l < r);
    }

    SECTION("Both are equal") {
        Expected<int> l = 42;
        Expected<int> r = 42;

        REQUIRE(l == r);
    }

    SECTION("Non-comparable") {
        Expected<int> l = 24;
        Expected<int> r = Error{"foo"};

        REQUIRE(!(l < r)); // NOLINT

        REQUIRE(!(l > r)); // NOLINT

        REQUIRE(!(l == r));
    }
}
