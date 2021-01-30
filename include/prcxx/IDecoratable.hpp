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
#include <any>

namespace prcxx {



template <class T>
class IDecoratable {
public:
    virtual ~IDecoratable() = default;

    [[nodiscard]]
    virtual bool has_getter() const noexcept = 0;

    [[nodiscard]]
    virtual Getter<T> getter() const noexcept = 0;

    virtual void set_getter(Getter<T> getter) noexcept = 0;

    virtual void reset_getter() noexcept = 0;
};

} // namesapce prcxx