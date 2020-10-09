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

#include <vector>
#include <memory>
#include <functional>
#include <any>

#include "prcxx/Expected.hpp"

namespace prcxx {

struct IObservable;

using IObservablePtr = std::shared_ptr<IObservable>;
using IObservableRef = std::reference_wrapper<IObservable>;
using Observers = std::vector<IObservableRef>;

struct IObservable {
    [[nodiscard]]
    virtual prcxx::Expected<std::any> resolve() = 0;

    virtual void update(std::any v) = 0;

    [[nodiscard]]
    virtual bool is_mutable() const = 0;

    [[nodiscard]]
    virtual bool is_dirty() const = 0;

    virtual void invalidate() = 0;

    virtual void copy_observers_from(const IObservable &observable) = 0;

    [[nodiscard]]
    virtual const Observers &get_observers() const = 0;

    [[nodiscard]]
    virtual IObservablePtr clone() const = 0;

    template<class T>
    friend
    class property;

private:
    [[maybe_unused]]
    virtual const std::any &value_ref() const = 0;
};

} //