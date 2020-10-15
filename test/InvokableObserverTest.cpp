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

#include <prcxx/InvokableObserver.hpp>

TEST_CASE("InvokableObserver implementation") {
    using namespace prcxx;

    SECTION("Constructed by value") {
        auto l = []{ return 42; };

        InvokableObserver obs(l);

        REQUIRE(l() == std::any_cast<int>(obs.resolve().value()));
    }

    SECTION("Constructed from tmp object") {
        InvokableObserver obs([]{ return 42; });

        REQUIRE(std::any_cast<int>(obs.resolve().value()) == 42);
    }

    SECTION("Is always immutable") {
        REQUIRE_FALSE(InvokableObserver([]{ return 42; }).is_mutable());
    }

    SECTION("Can be invalidated") {
        InvokableObserver obs([]{ return 42; });

        auto val = obs.resolve();

        REQUIRE(std::any_cast<int>(val.value()) == 42);
        REQUIRE_FALSE(obs.is_dirty());

        obs.invalidate();

        REQUIRE(obs.is_dirty());
    }

    SECTION("Evaluated only once") {
        int counter = 0;

        InvokableObserver obs([&counter]{ ++counter; return 42; });

        REQUIRE(std::any_cast<int>(obs.resolve().value()) == 42);
        REQUIRE(std::any_cast<int>(obs.resolve().value()) == 42);

        REQUIRE(counter == 1);
    }

    SECTION("Can be cloned") {
        InvokableObserver obs1([]{ return 42; });
        auto obs2 = obs1.clone();

        REQUIRE(std::any_cast<int>(obs1.resolve().value()) ==
                std::any_cast<int>(obs2->resolve().value()));
    }
}