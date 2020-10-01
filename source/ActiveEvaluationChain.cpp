#include "prcxx/ActiveEvaluationChain.hpp"

#include "prcxx/EvaluationChain.hpp"

namespace prcxx {

EvaluationChain &ActiveEvaluationChain::get()
{
    static thread_local EvaluationChain chain;
    return chain;
}

} // namespace prcxx