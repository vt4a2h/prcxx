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

#include "prcxx/IObservable.hpp"

namespace prcxx {

class EvaluationChain;

struct BaseObserver : public IObservable
{
    BaseObserver() = default;

    explicit BaseObserver(std::any v);

    const Observers &get_observers() const final;

    void copy_observers_from(const IObservable &observable)  final;

    void invalidate() override;

    static EvaluationChain &active_chain();

    void pre_process_active_chain();

    void post_process_active_chain();

protected:
    std::any value;
    mutable Observers observers;
};

} // namespace prcxx