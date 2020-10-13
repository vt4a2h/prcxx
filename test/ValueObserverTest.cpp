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

#include <prcxx/ValueObserver.hpp>

TEST_CASE("ValueObserver implementation") {
    using namespace prcxx;

    SECTION("Constructor by ref") {
        auto any = std::make_any<int>(42);
        ValueObserver<int> obs(any);

        REQUIRE(std::any_cast<int>(obs.resolve().value()) == 42);
    }

    SECTION("Constructor from rvalue") {
        auto any = std::make_any<int>(42);
        ValueObserver<int> obs(std::move(any));

        REQUIRE(std::any_cast<int>(obs.resolve().value()) == 42);
    }

    SECTION("Resolve") {
        ValueObserver<int> obs(std::make_any<int>(42));

        auto result = obs.resolve();

        REQUIRE(result.has_value());
        REQUIRE_FALSE(result.has_error());

        REQUIRE(std::any_cast<int>(result.value()) == 42);
    }

    SECTION("Update") {
        ValueObserver<int> obs(std::make_any<int>(42));

        obs.update(24);

        REQUIRE(std::any_cast<int>(obs.resolve().value()) == 24);
    }

    SECTION("Always mutable") {
        REQUIRE(ValueObserver<int>(std::make_any<int>(42)).is_mutable());
    }

    SECTION("Never dirty") {
        REQUIRE_FALSE(ValueObserver<int>(std::make_any<int>(42)).is_dirty());
    }

    SECTION("Can be cloned") {
        ValueObserver<int> obs1(std::make_any<int>(42));
        auto obs2 = obs1.clone();

        REQUIRE(std::any_cast<int>(obs1.resolve().value()) ==
                std::any_cast<int>(obs2->resolve().value()));
    }
}
