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

TEST_CASE("Custom property Setter") {
    using namespace prcxx;

    SECTION("Setter can be added") {
        property<int> p;

        p.set_setter([](int value) { return value + 1; });
        p = 41;

        REQUIRE(*p == 42);
    }

    SECTION("Setter can be checked") {
        property<int> p{41};
        p.set_setter([](int value) { return value + 1; });

        REQUIRE(p.has_setter());
    }

    SECTION("Setter can be reset") {
        property<int> p{41};
        p.set_setter([](int value) { return value + 1; });

        p.reset_setter();

        REQUIRE_FALSE(p.has_setter());
    }

    SECTION("Setter can be obtained") {
        property<int> p{41};
        p.set_setter([](int value) { return value + 1; });

        auto setter = p.setter();

        REQUIRE(std::invoke(setter, 41) == 42);
    }

    SECTION("The type of setter can be changed") {
        property<int, DefaultGetter<int>, std::function<int(std::any)>> p;

        p.set_setter([](std::any value) { return std::any_cast<int>(value) + 1; });
        p = 41;

        REQUIRE(*p == 42);
    }

    SECTION("Setter has no effect for unmodifiable properties") {
        property<int> p{wrap_invokable([]{ return 42; })};

        p.set_setter([](int value) { return value + 1; });
        p.set(0);

        REQUIRE(*p == 42);
    }
}
