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

#include <prcxx/ValueObservable.hpp>

TEST_CASE("ValueObservable implementation") {
    using namespace prcxx;

    SECTION("Constructor by ref") {
        auto any = std::make_any<int>(42);
        ValueObservable<int> obs(any);

        REQUIRE(std::any_cast<int>(obs.resolve().value()) == 42);
    }

    SECTION("Constructor from rvalue") {
        auto any = std::make_any<int>(42);
        ValueObservable<int> obs(std::move(any));

        REQUIRE(std::any_cast<int>(obs.resolve().value()) == 42);
    }

    SECTION("Resolve") {
        ValueObservable<int> obs(std::make_any<int>(42));

        auto result = obs.resolve();

        REQUIRE(result.has_value());
        REQUIRE_FALSE(result.has_error());

        REQUIRE(std::any_cast<int>(result.value()) == 42);
    }

    SECTION("Update") {
        ValueObservable<int> obs(std::make_any<int>(42));

        obs.update(24);

        REQUIRE(std::any_cast<int>(obs.resolve().value()) == 24);
    }

    SECTION("Always mutable") {
        REQUIRE(ValueObservable<int>(std::make_any<int>(42)).is_mutable());
    }

    SECTION("Never dirty") {
        REQUIRE_FALSE(ValueObservable<int>(std::make_any<int>(42)).is_dirty());
    }

    SECTION("Can be cloned") {
        ValueObservable<int> obs1(std::make_any<int>(42));
        auto obs2 = obs1.clone();

        REQUIRE(std::any_cast<int>(obs1.resolve().value()) ==
                std::any_cast<int>(obs2->resolve().value()));
    }
}
