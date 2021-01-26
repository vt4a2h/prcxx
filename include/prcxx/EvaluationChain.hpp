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

#include <stack>

#include "prcxx/IObservable.hpp"
#include "prcxx/Expected.hpp"

namespace prcxx {

struct EvaluationChain
{
    [[nodiscard]]
    bool empty() const;

    [[nodiscard]]
    bool contains_error() const;

    void push(IObservableWeakPtr ref);

    IObservableWeakPtr top();
    void pop();

    void register_error(Error error);
    Error extract_last_error();

    [[nodiscard]]
    Error error() const;

private:
    std::stack<IObservableWeakPtr> properties;
    Error last_error;
};

} // namespace prcxx