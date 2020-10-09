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

TEST_CASE("Expected is constructable") {
    using namespace prcxx;

    SECTION("From value") {
        Expected<int> expected = 42;

        REQUIRE(expected.has_value());

        REQUIRE(expected.value() == 42);

        REQUIRE(*expected == 42);
    }

    SECTION("From error") {
        Expected<int> expected = Error{"foo"};

        REQUIRE(expected.has_error());

        REQUIRE(expected.error().text == "foo");
    }
}
