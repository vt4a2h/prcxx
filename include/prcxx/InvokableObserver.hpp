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

#include "prcxx/BaseObserver.hpp"
#include "prcxx/EvaluationChain.hpp"
#include "prcxx/Concepts.hpp"

namespace prcxx {

template <Invokable F>
struct ScopedFuncInvoker {
    ScopedFuncInvoker(F f) : f(std::move(f)) {}
    ~ScopedFuncInvoker() { std::invoke(f); }
    F f;
};
template <Invokable F> ScopedFuncInvoker(F)
-> ScopedFuncInvoker<std::decay_t<F>>;

template <Invokable Callable>
struct InvokableObserver : public BaseObserver
{
    explicit InvokableObserver(const Callable &v)
        : callable(v)
    {}

    explicit InvokableObserver(Callable &&v) noexcept
        : callable(std::move(v))
    {}

    [[nodiscard]]
    prcxx::Expected<std::any> resolve() override
    {
        if (visiting) {
            active_chain().register_error(
                Error{.text = "The cycle is detected. The property cannot depend on itself"});
            return active_chain().error();
        }

        ScopedVisitingSetter visiting_setter(visiting);

        if (is_dirty()) {
            pre_process_active_chain();
            ScopedFuncInvoker post_process([this]{ post_process_active_chain(); });

            value = std::invoke(callable);
            if (active_chain().contains_error()) {
                value.reset();
                return active_chain().extract_last_error();
            }

            dirty = false;
        }

        return value;
    };

    void update(std::any) final {}
    bool is_mutable() const final { return false; }

    struct ScopedVisitingSetter
    {
        explicit ScopedVisitingSetter(bool &c)
                : current(c)
        { current = true; }

        ~ScopedVisitingSetter() { current = false; }

        bool &current;
    };

    bool is_dirty() const override
    {
        return dirty;
    }

    void invalidate() final
    {
        dirty = true;
        BaseObserver::invalidate();
    }

    IObservableUniquePtr clone() const override
    {
        // Leave all other data in the default state
        // (will be re-evaluated upon the first call)
        return std::make_unique<InvokableObserver<Callable>>(callable);
    }

    std::decay_t<Callable> callable;
    mutable bool dirty = true;
    mutable bool visiting = false;

private:
    const std::any &value_ref() const override
    {
        assert(!is_dirty());
        return value;
    }
};

} // namespace prcxx
