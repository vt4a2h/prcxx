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