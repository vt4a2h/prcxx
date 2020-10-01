#pragma once

#include <string>
#include <variant>

namespace prcxx {

struct Error
{
    std::string text;
};

template <class Value>
class Expected : public std::variant<Value, Error>
{
public:
    using std::variant<Value, Error>::variant;

    [[nodiscard]]
    constexpr bool has_value() const
    {
        return std::holds_alternative<Value>(*this);
    }

    [[nodiscard]]
    constexpr bool has_error() const
    {
        return std::holds_alternative<Error>(*this);
    }

    [[nodiscard]]
    Value value() const
    {
        assert(has_value());
        return std::get<Value>(*this);
    }

    [[nodiscard]]
    Error error() const
    {
        assert(has_error());
        return std::get<Error>(*this);
    }

    [[nodiscard]]
    Value operator*() const
    {
        return value();
    }

    friend constexpr std::partial_ordering operator<=>(const Expected<Value> &lhs, const Expected<Value> &rhs)
    {
        if (lhs.has_error() || rhs.has_error())
            return std::partial_ordering::unordered;

        const auto &l = std::get<Value>(lhs);
        const auto &r = std::get<Value>(rhs);

        if (l > r)
            return std::partial_ordering::greater;
        if (l < r)
            return std::partial_ordering::less;
        if (l == r)
            return std::partial_ordering::equivalent;

        return std::partial_ordering::unordered;
    }

    friend bool operator ==(const Expected<Value> &lhs, const Expected<Value> &rhs)
    {
        return std::is_eq(lhs <=> rhs);
    }
};

} // prcxx