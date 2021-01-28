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
#include <prcxx/DecoratableBase.hpp>

namespace prcxx {

bool DecoratableBase::has_getter() const noexcept
{
    return !!m_getter;
}

Getter DecoratableBase::getter() const noexcept
{
    return m_getter;
}

void DecoratableBase::set_getter(Getter getter) noexcept
{
    m_getter = getter;
}

void DecoratableBase::reset_getter() noexcept
{
    m_getter = {};
}

} // namespace prcxx
