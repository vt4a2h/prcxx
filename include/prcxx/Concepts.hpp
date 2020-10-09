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

#include <type_traits>

namespace prcxx {

template <class F>
concept Invokable = std::is_invocable_v<std::decay_t<F>>;

} // namespace prcxx

