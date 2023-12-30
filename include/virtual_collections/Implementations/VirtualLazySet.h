#pragma once

#include <memory>

#include "../Interfaces/IVirtualSet.h"
#include "Sets/BooleanKeySet.h"
#include "Sets/FloatingPointKeySet.h"
#include "Sets/IntegralKeySet.h"
#include "Sets/PointerKeySet.h"
#include "Sets/StringKeySet.h"

namespace VirtualCollections {

    class VirtualLazySet : public IVirtualSet {
        std::unique_ptr<Sets::IBooleanKeySet>       _bools    = nullptr;
        std::unique_ptr<Sets::IIntegralKeySet>      _ints     = nullptr;
        std::unique_ptr<Sets::IFloatingPointKeySet> _floats   = nullptr;
        std::unique_ptr<Sets::IStringKeySet>        _strings  = nullptr;
        std::unique_ptr<Sets::IPointerKeySet>       _pointers = nullptr;

    public:
        Sets::IBooleanKeySet* bools() override {
            if (!_bools) _bools = std::make_unique<Sets::BooleanKeySet>();
            return _bools.get();
        }
        Sets::IIntegralKeySet* ints() override {
            if (!_ints) _ints = std::make_unique<Sets::IntegralKeySet>();
            return _ints.get();
        }
        Sets::IFloatingPointKeySet* floats() override {
            if (!_floats) _floats = std::make_unique<Sets::FloatingPointKeySet>();
            return _floats.get();
        }
        Sets::IStringKeySet* strings() override {
            if (!_strings) _strings = std::make_unique<Sets::StringKeySet>();
            return _strings.get();
        }
        Sets::IPointerKeySet* pointers() override {
            if (!_pointers) _pointers = std::make_unique<Sets::PointerKeySet>();
            return _pointers.get();
        }

        const Sets::IBooleanKeySet* bools() const override {
            if (_bools) return _bools.get();
            else return nullptr;
        }
        const Sets::IIntegralKeySet* ints() const override {
            if (_ints) return _ints.get();
            else return nullptr;
        }
        const Sets::IFloatingPointKeySet* floats() const override {
            if (_floats) return _floats.get();
            else return nullptr;
        }
        const Sets::IStringKeySet* strings() const override {
            if (_strings) return _strings.get();
            else return nullptr;
        }
        const Sets::IPointerKeySet* pointers() const override {
            if (_pointers) return _pointers.get();
            else return nullptr;
        }

        unsigned int size() const override {
            return (_bools ? _bools->size() : 0) + (_ints ? _ints->size() : 0) +
                   (_floats ? _floats->size() : 0) + (_strings ? _strings->size() : 0) +
                   (_pointers ? _pointers->size() : 0);
        }

        void foreach_key_and_value(ForEachElementFn* callback) const override {
            if (_bools) _bools->foreach_key_and_value(callback);
            if (_ints) _ints->foreach_key_and_value(callback);
            if (_floats) _floats->foreach_key_and_value(callback);
            if (_strings) _strings->foreach_key_and_value(callback);
            if (_pointers) _pointers->foreach_key_and_value(callback);
        }

        void foreach_value(ForEachItemFn* callback) const override {
            if (_bools) _bools->foreach_value(callback);
            if (_ints) _ints->foreach_value(callback);
            if (_floats) _floats->foreach_value(callback);
            if (_strings) _strings->foreach_value(callback);
            if (_pointers) _pointers->foreach_value(callback);
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
