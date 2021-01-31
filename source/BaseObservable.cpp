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
#include "prcxx/BaseObservable.hpp"
#include "prcxx/ActiveEvaluationChain.hpp"
#include "prcxx/EvaluationChain.hpp"

#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/action/push_back.hpp>
#include <range/v3/algorithm/for_each.hpp>

namespace prcxx {

    namespace r = ranges;
    namespace rv = r::views;
    namespace ra = r::actions;

    static const auto validObservers = rv::filter([](auto &&o) { return !o.expired(); });

    BaseObservable::BaseObservable(std::any v)
            : value(std::move(v))
    {}

    const Observers &BaseObservable::get_observers() const
    {
        return this->observers;
    }

    void BaseObservable::copy_observers_from(const IObservable &observable)
    {
        auto src = observable.get_observers() | validObservers;
        observers.reserve(r::distance(src) + observers.size());
        ra::push_back(observers, src);
    }

    void BaseObservable::invalidate()
    {
        auto toRefs = rv::transform([](auto &&o) { return o.lock().get(); });
        r::for_each(observers | validObservers | toRefs, &IObservable::invalidate);
    }

    EvaluationChain &BaseObservable::active_chain()
    {
        return ActiveEvaluationChain::get();
    }

    void BaseObservable::pre_process_active_chain()
    {
        observers.clear();
        if (!active_chain().empty()) {
            if (auto top = active_chain().top(); !top.expired())
                observers.emplace_back(top);
        } else {
            active_chain().push(this->as_weak_ptr());
        }
    }

    void BaseObservable::post_process_active_chain()
    {
        if (auto wr = active_chain().top(); !wr.expired() && wr.lock().get() == this)
            active_chain().pop();
    }

    IObservableWeakPtr BaseObservable::as_weak_ptr() noexcept
    {
        return this->weak_from_this();
    }

} // namespace prcxx

