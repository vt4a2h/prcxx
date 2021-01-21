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

TEST_CASE("Properties can be constructed") {
    using namespace prcxx;

    SECTION("Default constructor") {
        property<int> p{};

        REQUIRE_FALSE(p.has_value());
    }

    SECTION("Resolve constructor") {
        int v = 42;
        property<int> p(v);

        REQUIRE(*p.get() == 42);
    }

    SECTION("Rvalue reference constructor") {
        std::string s{"42"};
        property<std::string> p(std::move(s));

        REQUIRE(*p.get() == "42");
    }

    SECTION("Observable constructor") {
        property<std::string> p(wrap_invokable([]() -> std::string { return "Hi!"; }));

        REQUIRE(p.has_value());
    }

    SECTION("Copy constructor") {
        property<int> p1(42);
        property<int> p2(p1); // NOLINT

        REQUIRE(*p1.get() == *p2.get());
    }

    SECTION("Move constructor") {
        property<std::string> p1("42");
        property<std::string> p2(std::move(p1));

        REQUIRE(*p2.get() == "42");
    }

    SECTION("Assigment operator") {
        property<int> p1(42);
        property<int> p2{};

        p2 = p1;

        REQUIRE(*p1.get() == *p2.get());
    }

    SECTION("Move operator") {
        property<std::string> p1("42");
        property<std::string> p2{};

        p2 = std::move(p1);

        REQUIRE(*p2.get() == "42");
    }

    SECTION("Assigment operator (value)") {
        property<int> p(32);

        p = 42;

        REQUIRE(*p.get() == 42);
    }
}
