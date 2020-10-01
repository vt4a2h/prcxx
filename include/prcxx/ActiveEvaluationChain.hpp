#pragma once

namespace prcxx {

class EvaluationChain;

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
