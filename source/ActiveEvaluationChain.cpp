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
#include "prcxx/ActiveEvaluationChain.hpp"

#include "prcxx/EvaluationChain.hpp"

namespace prcxx {

EvaluationChain &ActiveEvaluationChain::get()
{
    static thread_local EvaluationChain chain;
    return chain;
}

} // namespace prcxx