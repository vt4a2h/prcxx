#include "catch.hpp"

#include <string>

#include <prcxx/property.hpp>

namespace Catch {
template<>
struct StringMaker<prcxx::property<int>> {
    static std::string convert(const prcxx::property<int> &p) {
        if (p.has_value()) {
            auto res = p.get();
            return res.has_value() ? std::to_string(res.value()) : res.error().text;
        }
        return "The property is empty";
    }
};

template<>
struct StringMaker<prcxx::property<std::string>> {
    static std::string convert(const prcxx::property<std::string> &p) {
        if (p.has_value()) {
            auto res = p.get();
            return res.has_value() ? res.value() : res.error().text;
        }
        return "The property is empty";
    }
};
}

TEST_CASE("properties can be constructed") {
    using namespace prcxx;

    SECTION("default constructor") {
        property<int> p{};

        REQUIRE_FALSE(p.has_value());
    }

    SECTION("resolve constructor") {
        int v = 42;
        property<int> p(v);

        REQUIRE(*p.get() == 42);
    }

    SECTION("rvalue reference constructor") {
        std::string s{"42"};
        property<std::string> p(std::move(s));

        REQUIRE(*p.get() == "42");
    }

    SECTION("observable constructor") {
        property<std::string> p(wrap_invokable([]() -> std::string { return "Hi!"; }));

        REQUIRE(p.has_value());
    }


    SECTION("copy constructor") {
        property<int> p1(42);
        property<int> p2(p1); // NOLINT

        REQUIRE(*p1.get() == *p2.get());
    }

    SECTION("move constructor") {
        property<std::string> p1("42");
        property<std::string> p2(std::move(p1));

        REQUIRE(*p2.get() == "42");
    }

    SECTION("assigment operator") {
        property<int> p1(42);
        property<int> p2{};

        p2 = p1;

        REQUIRE(*p1.get() == *p2.get());
    }

    SECTION("move operator") {
        property<std::string> p1("42");
        property<std::string> p2{};

        p2 = std::move(p1);

        REQUIRE(*p2.get() == "42");
    }
}

TEST_CASE("properties can be compared") {
    using namespace prcxx;

    SECTION("empty properties are equal") {
        property<int> p1;
        property<int> p2;

        REQUIRE(p1 == p2);
    }

    SECTION("equal") {
        property<int> p1(1);
        property<int> p2(2);

        REQUIRE_FALSE(p1 == p2);
    }

    SECTION("p2 is greater than p1") {
        property<int> p1(1);
        property<int> p2(2);

        REQUIRE(p2 > p1);
    }

    SECTION("p1 is less than p2") {
        property<int> p1(1);
        property<int> p2(2);

        REQUIRE(p1 < p2);
    }

    SECTION("p1 and p2 are not related") {
        property<int> p1;
        property<int> p2(2);

        REQUIRE_FALSE((p1 < p2 || p1 > p2 || p1 == p2)); // NOLINT
    }
}

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

TEST_CASE("Cycles detection") {
    using namespace prcxx;

    SECTION("There is no value when a cycle detected") {
        property<int> p1(wrap_invokable([&p1] {
            auto v = p1.get();

            REQUIRE_FALSE(v.has_value());

            return v.has_value() ? *v : -1;
        }));

        REQUIRE_FALSE(p1.get().has_value());
    }
}