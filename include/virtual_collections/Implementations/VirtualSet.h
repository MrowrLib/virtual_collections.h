#pragma once

#include <memory>

#include "../Interfaces/IVirtualSet.h"
#include "Sets/BooleanKeySet.h"
#include "Sets/FloatingPointKeySet.h"
#include "Sets/IntegralKeySet.h"
#include "Sets/PointerKeySet.h"
#include "Sets/StringKeySet.h"

namespace VirtualCollections {

    class VirtualSet : public IVirtualSet {
        std::unique_ptr<IBooleanKeySet>       _bools;
        std::unique_ptr<IIntegralKeySet>      _ints;
        std::unique_ptr<IFloatingPointKeySet> _floats;
        std::unique_ptr<IStringKeySet>        _strings;
        std::unique_ptr<IPointerKeySet>       _pointers;

    public:
        IBooleanKeySet* bools() override {
            if (!_bools) _bools = std::make_unique<Sets::BooleanKeySet>();
            return _bools.get();
        }

        IIntegralKeySet* ints() override {
            if (!_ints) _ints = std::make_unique<Sets::IntegralKeySet>();
            return _ints.get();
        }

        IFloatingPointKeySet* floats() override {
            if (!_floats) _floats = std::make_unique<Sets::FloatingPointKeySet>();
            return _floats.get();
        }

        IStringKeySet* strings() override {
            if (!_strings) _strings = std::make_unique<Sets::StringKeySet>();
            return _strings.get();
        }

        IPointerKeySet* pointers() override {
            if (!_pointers) _pointers = std::make_unique<Sets::PointerKeySet>();
            return _pointers.get();
        }

        unsigned int size() const override {
            return (_bools ? _bools->size() : 0) + (_ints ? _ints->size() : 0) +
                   (_floats ? _floats->size() : 0) + (_strings ? _strings->size() : 0) +
                   (_pointers ? _pointers->size() : 0);
        }

        void foreach_element(ForEachElementFn* callback) const override {
            if (_bools) _bools->foreach_element(callback);
            if (_ints) _ints->foreach_element(callback);
            if (_floats) _floats->foreach_element(callback);
            if (_strings) _strings->foreach_element(callback);
            if (_pointers) _pointers->foreach_element(callback);
        }

        void foreach_item(ForEachItemFn* callback) const override {
            if (_bools) _bools->foreach_item(callback);
            if (_ints) _ints->foreach_item(callback);
            if (_floats) _floats->foreach_item(callback);
            if (_strings) _strings->foreach_item(callback);
            if (_pointers) _pointers->foreach_item(callback);
        }

        void clear() override {
            if (_bools) _bools->clear();
            if (_ints) _ints->clear();
            if (_floats) _floats->clear();
            if (_strings) _strings->clear();
            if (_pointers) _pointers->clear();
        }
    };
}
