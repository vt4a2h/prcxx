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

#include "prcxx/BaseObserver.hpp"

namespace prcxx {

template <class Value>
struct ValueObserver : public BaseObserver
{
    explicit ValueObserver(const std::any &v)
            : BaseObserver(v)
    {}

    explicit ValueObserver(std::any &&v) noexcept
            : BaseObserver(std::move(v))
    {}

    [[nodiscard]]
    prcxx::Expected<std::any> resolve() override
    {
        pre_process_active_chain();
        post_process_active_chain();
        return value;
    };

    void update(std::any v) override
    {
        if (std::any_cast<Value&>(value) != std::any_cast<Value&>(v)) {
            value = std::move(v);
            invalidate();
        }
    }

    bool is_mutable() const override { return true; }

    // Cannot be dirty
    bool is_dirty() const final { return false; }

    IObservableUniquePtr clone() const override
    {
        return std::make_unique<ValueObserver<Value>>(value);
    }

private:
    const std::any &value_ref() const override
    {
        assert(!is_dirty());
        return value;
    }
};

} // namespace prcxx
