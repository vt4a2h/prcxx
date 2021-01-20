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

#include <string>

#include "SourceLocation.hpp"

namespace prcxx {

struct Error
{
    std::string text;
};

namespace detail {

    Error with_source_location(Error err, const source_location &sl);

}

} // namespace prcxx
