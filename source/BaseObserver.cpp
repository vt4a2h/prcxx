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
#include "prcxx/BaseObserver.hpp"
#include "prcxx/ActiveEvaluationChain.hpp"
#include "prcxx/EvaluationChain.hpp"

namespace prcxx {

    BaseObserver::BaseObserver(std::any v)
            : value(std::move(v))
    {}

    const Observers &BaseObserver::get_observers() const
    {
        return this->observers;
    }

    void BaseObserver::copy_observers_from(const IObservable &observable)
    {
        const auto &src = observable.get_observers();
        observers.reserve(src.size() + observers.size());
        std::copy(src.cbegin(), src.cend(), std::back_inserter(observers));
    }

    void BaseObserver::invalidate()
    {
        for (auto &&observer : observers)
            observer.get().invalidate();
    }

    EvaluationChain &BaseObserver::active_chain()
    {
        return ActiveEvaluationChain::get();
    }

    void BaseObserver::pre_process_active_chain()
    {
        observers.clear();
        if (!active_chain().empty()) {
            auto &top = active_chain().top().get();
            observers.emplace_back(top);
        } else {
            active_chain().push(*this);
        }
    }

    void BaseObserver::post_process_active_chain()
    {
        if (&active_chain().top().get() == this)
            active_chain().pop();
    }

} // namespace prcxx

