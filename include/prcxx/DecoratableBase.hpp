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

template <class Value, class Getter = std::function<Value(const Value&)>>
    requires std::is_invocable_r_v<std::decay_t<Value>, Getter, std::decay_t<Value>>
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
    }

    void move_decorators_from(DecoratableBase &&src) noexcept
    {
        m_getter = std::move(src.m_getter);
    }

private:
    Getter m_getter;
};

} // namespace prcxx
