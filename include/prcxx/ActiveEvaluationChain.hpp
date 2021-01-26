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

namespace prcxx {

struct EvaluationChain;

class ActiveEvaluationChain
{
public:
    ActiveEvaluationChain(const ActiveEvaluationChain&) = delete;
    ActiveEvaluationChain(ActiveEvaluationChain&&) = delete;
    ActiveEvaluationChain &operator=(const ActiveEvaluationChain &) = delete;
    ActiveEvaluationChain &operator=(ActiveEvaluationChain &&) = delete;

    [[nodiscard]]
    static EvaluationChain &get();

private:
    ActiveEvaluationChain() = default;
};

} // namespace prcxx
