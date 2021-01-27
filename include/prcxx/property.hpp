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
#pragma once

#include <variant>
#include <type_traits>
#include <any>
#include <cassert>
#include <vector>
#include <stack>
#include <string>
#include <compare>

#include "Expected.hpp"
#include "IObservable.hpp"
#include "EvaluationChain.hpp"
#include "ActiveEvaluationChain.hpp"
#include "BaseObserver.hpp"
#include "ValueObserver.hpp"
#include "InvokableObserver.hpp"
#include "SourceLocation.hpp"

namespace prcxx {

template <Invokable Observable>
IObservableSharedPtr wrap_invokable(Observable &&observable)
{
    return std::make_unique<
        InvokableObserver<std::decay_t<Observable>>>(
            std::forward<Observable>(observable));
}

template <class Value>
IObservableSharedPtr wrap_value(Value &&value)
{
    return std::make_unique<
        ValueObserver<std::decay_t<Value>>>(
            std::forward<Value>(value));
}

template <class T>
class property
{
public:
    property() = default;

    explicit property(const T& v)
        : value(wrap_value(v))
    {}
    explicit property(T&& v) noexcept
        : value(wrap_value(std::move(v)))
    {}

    explicit property(IObservableSharedPtr observable) noexcept
        : value(std::move(observable))
    {}

    property(const property<T>& v)
        : value(v.value->clone())
    {}
    property(property<T>&& v) noexcept
        : value(std::move(v.value))
    {}
    property<T> &operator=(const property<T> &v)
    {
        if (&v != this)
            this->value = v.value->clone();

        return *this;
    }
    property<T> &operator=(property<T> &&v) noexcept
    {
        if (&v != this)
            this->value = std::move(v.value);

        return *this;
    }
    property<T> &operator=(const T &v)
    {
        set(v);

        return *this;
    }

    ~property() = default;

    friend constexpr std::partial_ordering operator<=>(const property<T> &lhs, const property<T> &rhs)
    {
        if (!lhs.has_value() && !rhs.has_value())
            return std::partial_ordering::equivalent;

        if (!lhs.has_value() || !rhs.has_value())
            return std::partial_ordering::unordered;

        // Both values have been resolved without errors, we can avoid extra copies
        if (!lhs.value->is_dirty() && !rhs.value->is_dirty())
            return lhs.as_ref() <=> rhs.as_ref();

        return lhs.get() <=> rhs.get();
    }

    friend bool operator ==(const property<T> &lhs, const property<T> &rhs)
    {
        return std::is_eq(lhs <=> rhs);
    }

    explicit operator T() const
        requires std::is_destructible_v<T>
    {
        auto result = get();
        return result.has_value() ? result.value() : T();
    }

    T operator*() const
        requires std::is_destructible_v<T>
    {
        return static_cast<T>(*this);
    }

    [[nodiscard]]
    Expected<T> get(const source_location &sl = source_location::current()) const
    {
        if (has_value()) {
            auto result = value->resolve();
            if (std::holds_alternative<std::any>(result))
                return std::any_cast<T>(std::get<std::any>(std::move(result)));
            else
                return detail::with_source_location(std::get<Error>(std::move(result)), sl);
        }

        return detail::with_source_location({"The property has no value"}, sl);
    }

    [[nodiscard]]
    bool has_value() const { return !!value; }

    void set(const T& v)
    {
        if (has_value()) {
            if (value->is_mutable())
                value->update(v);
        } else {
            value = wrap_value(v);
        }
    }

    void reset(IObservableSharedPtr observable = nullptr)
    {
        if (value) {
            value->invalidate();

            if (observable)
                observable->copy_observers_from(*value);
        }

        value = std::move(observable);
    }

private: // Methods
    const T &as_ref() const
    {
        assert(has_value());
        assert(!value->is_dirty());
        return std::any_cast<const T&>(value->value_ref());
    }

private:
    IObservableSharedPtr value;
};

} // prcxx
