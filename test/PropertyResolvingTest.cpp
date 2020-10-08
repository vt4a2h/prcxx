#include "catch.hpp"

#include <string>

#include <prcxx/property.hpp>

TEST_CASE("a property can be resolved") {
    using namespace prcxx;

    SECTION("simple resolve") {
        property<std::string> p(wrap_invokable([]() -> std::string { return "Hi!"; }));

        REQUIRE(*p.get() == "Hi!");
    }

    SECTION("resolve with binding dependency") {
        property<std::string> p0(wrap_invokable([]() -> std::string { return "Hello"; }));

        property<std::string> p(wrap_invokable(
                [&p0]() -> std::string {
                    return *p0.get() + " world!";
                }));

        REQUIRE(*p.get() == "Hello world!");

        p0.reset(wrap_value(std::string("No")));

        REQUIRE(*p.get() == "No world!");
    }

    SECTION("resolve with value dependency") {
        property<std::string> p0("Hello");

        property<std::string> p(wrap_invokable(
                [&p0]() -> std::string {
                    return *p0.get() + " world!";
                }));

        REQUIRE(*p.get() == "Hello world!");

        p0.set("No");

        REQUIRE(*p.get() == "No world!");
    }

    SECTION("re-evaluates only when some certain properties changed") {
        property<std::string> p0("p0");
        property<std::string> p1("p1");

        int counter = 0;
        property<std::string> p(wrap_invokable([&] {
            ++counter;

            auto p0_val = *p0.get();
            if (p0_val == "p0")
                return p0_val;

            return *p1.get();
        }));

        REQUIRE(counter == 0);

        REQUIRE(*p.get() == "p0");
        REQUIRE(counter == 1);

        p1.set("~p1");

        REQUIRE(*p.get() == "p0");
        REQUIRE(counter == 1);

        p0.set("~p0");

        REQUIRE(*p.get() == "~p1");
        REQUIRE(counter == 2);

        p0.set("p0");

        REQUIRE(*p.get() == "p0");
        REQUIRE(counter == 3);
    }
}