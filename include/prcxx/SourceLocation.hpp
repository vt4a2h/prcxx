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

#ifdef __has_include
#   if __has_include(<source_location>)
#       include <source_location>
#       define SOURCE_LOCATION std::source_location
#    elif __has_include(<experimental/source_location>)
#       include <experimental/source_location>
#       define SOURCE_LOCATION std::experimental::source_location
#    else
#       Error: missing <source_location>
#    endif
#endif

namespace prcxx {

using source_location = SOURCE_LOCATION;

}