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

#include <functional>
#include <functional>

namespace prcxx {

template <class Value>
using DefaultGetter = std::function<Value(const Value&)>;

template <class Value>
using DefaultSetter = std::function<Value(const Value&)>;

template <class Value, class Getter = DefaultGetter<Value>, class Setter = DefaultSetter<Value>>
    requires (std::is_invocable_r_v<std::decay_t<Value>, Getter, std::decay_t<Value>> &&
              std::is_invocable_r_v<std::decay_t<Value>, Setter, std::decay_t<Value>>)
class DecoratableBase {
public:
    virtual ~DecoratableBase() = default;

    [[nodiscard]]
    bool has_getter() const noexcept
    {
        return !!m_getter;
    }

    [[nodiscard]]
    Getter getter() const noexcept
    {
        return m_getter;
    }

    void set_getter(const Getter &getter)
    {
        m_getter = getter;
    }

    void reset_getter() noexcept
        requires std::is_default_constructible_v<Getter>
    {
        m_getter = {};
    }

    void copy_decorators_from(const DecoratableBase &src) noexcept
    {
        m_getter = src.getter();
        m_setter = src.setter();
    }

    void move_decorators_from(DecoratableBase &&src) noexcept
    {
        m_getter = std::move(src.m_getter);
        m_setter = std::move(src.m_setter);
    }

    [[nodiscard]]
    bool has_setter() const noexcept
    {
        return !!m_setter;
    }

    [[nodiscard]]
    Setter setter() const noexcept
    {
        return m_setter;
    }

    void set_setter(const Setter &setter)
    {
        m_setter = setter;
    }

    void reset_setter() noexcept
        requires std::is_default_constructible_v<Setter>
    {
        m_setter = {};
    }

private:
    Getter m_getter;
    Setter m_setter;
};

} // namespace prcxx
