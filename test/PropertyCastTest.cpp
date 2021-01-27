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

TEST_CASE("Property can be casted") {
    using namespace prcxx;

    SECTION("Simple cast of the valid property") {
        property<int> p{42};

        REQUIRE(static_cast<int>(p) == 42);
    }

    struct Foo {
        enum class Tag { SomeState, Default };
        Tag tag = Tag::Default;
    };

    SECTION("Invalid property returns default result") {
        property<Foo> p;

        REQUIRE(static_cast<Foo>(p).tag == Foo::Tag::Default);
    }

    SECTION("Operator *") {
        property<int> p{42};

        REQUIRE(*p == 42);
    }

    SECTION("Operator * returns default result for the invalid property") {
        property<Foo> p;

        REQUIRE((*p).tag == Foo::Tag::Default);
    }
}
