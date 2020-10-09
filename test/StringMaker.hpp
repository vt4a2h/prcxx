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

#include "catch.hpp"

#include <string>

#include <prcxx/property.hpp>

namespace Catch {
    template<>
    struct StringMaker<prcxx::property<int>> {
        static std::string convert(const prcxx::property<int> &p) {
            if (p.has_value()) {
                auto res = p.get();
                return res.has_value() ? std::to_string(res.value()) : res.error().text;
            }
            return "The property is empty";
        }
    };

    template<>
    struct StringMaker<prcxx::property<std::string>> {
        static std::string convert(const prcxx::property<std::string> &p) {
            if (p.has_value()) {
                auto res = p.get();
                return res.has_value() ? res.value() : res.error().text;
            }
            return "The property is empty";
        }
    };
}