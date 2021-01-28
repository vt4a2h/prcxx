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

using Getter = std::function<std::any(std::any)>;

class IDecoratable {
public:
    virtual ~IDecoratable() = default;

    [[nodiscard]]
    virtual bool has_getter() const noexcept = 0;

    [[nodiscard]]
    virtual Getter getter() const noexcept = 0;

    virtual void set_getter(Getter getter) noexcept = 0;

    virtual void reset_getter() noexcept = 0;
};

} // namesapce prcxx