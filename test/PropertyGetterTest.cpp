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

#include <any>

#include <prcxx/property.hpp>

TEST_CASE("Custom property getter") {
    using namespace prcxx;

    SECTION("Getter can be added") {
        property<int> p{41};
        p.set_getter([](int value) { return value + 1; });

        REQUIRE(*p == 42);
    }

    SECTION("Getter can be checked") {
        property<int> p{41};
        p.set_getter([](int value) { return value + 1; });

        REQUIRE(p.has_getter());
    }

    SECTION("Getter can be reset") {
        property<int> p{41};
        p.set_getter([](int value) { return value + 1; });

        p.reset_getter();

        REQUIRE_FALSE(p.has_getter());
    }

    SECTION("Getter can be obtained") {
        property<int> p{41};
        p.set_getter([](int value) { return value + 1; });

        auto getter = p.getter();

        REQUIRE(std::invoke(getter, 41) == 42);
    }

    SECTION("The type of getter can be changed") {
        property<int, std::function<int(std::any)>> p{41};
        p.set_getter([](std::any value) { return std::any_cast<int>(value) + 1; });

        REQUIRE(*p == 42);
    }
}