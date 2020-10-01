#pragma once

#include <type_traits>

namespace prcxx {

template <class F>
concept Invokable = std::is_invocable_v<std::decay_t<F>>;

} // namespace prcxx

