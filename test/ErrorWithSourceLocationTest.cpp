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

#include <prcxx/Error.hpp>

TEST_CASE("Error extensibility") {
    using namespace prcxx::detail;

    SECTION("Source location can be added") {
        prcxx::Error error{"test error message"};

        auto with_sl = with_source_location(error, prcxx::source_location::current());

        REQUIRE(with_sl.text.starts_with("test error message"));
        REQUIRE(with_sl.text.ends_with("ErrorWithSourceLocationTest.cpp:21:0)"));
    }
}