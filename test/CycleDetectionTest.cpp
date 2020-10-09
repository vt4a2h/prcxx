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

#include <prcxx/property.hpp>

TEST_CASE("Cycles detection") {
    using namespace prcxx;

    SECTION("There is no value when a cycle is detected") {
        property<int> p1(wrap_invokable([&p1] {
            auto v = p1.get();

            REQUIRE_FALSE(v.has_value());

            return v.has_value() ? *v : -1;
        }));

        REQUIRE_FALSE(p1.get().has_value());
    }
}