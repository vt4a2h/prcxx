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

#include "IDecoratable.hpp"

namespace prcxx {

class DecoratableBase : public IDecoratable {
public:
    bool has_getter() const noexcept override;

    Getter getter() const noexcept override;

    void set_getter(Getter getter) noexcept override;

    void reset_getter() noexcept override;

private:
    Getter m_getter;
};

} // namespace prcxx
