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
#include "prcxx/Error.hpp"

#include <fmt/format.h>

namespace prcxx::detail {

    Error with_source_location(prcxx::Error err, const prcxx::source_location &sl) // NOLINT
    {
        return {fmt::format("{} ({}:{}:{})", std::move(err.text), sl.file_name(), sl.line(), sl.column())};
    }

} // prcxx::detail
