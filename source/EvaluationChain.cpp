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
#include "prcxx/EvaluationChain.hpp"

namespace prcxx {

bool EvaluationChain::empty() const
{
    return properties.empty();
}

bool EvaluationChain::contains_error() const
{
    return !last_error.text.empty();
}

void EvaluationChain::push(IObservableRef ref)
{
    properties.push(std::move(ref));
}

IObservableRef EvaluationChain::top()
{
    return properties.top();
}

void EvaluationChain::pop()
{
    properties.pop();
}

void EvaluationChain::register_error(Error error)
{
    last_error = std::move(error);
}

Error EvaluationChain::extract_last_error()
{
    Error tmp;
    std::swap(tmp, last_error);
    return tmp;
}

Error EvaluationChain::error() const
{
    return last_error;
}

} // namespace prcxx
