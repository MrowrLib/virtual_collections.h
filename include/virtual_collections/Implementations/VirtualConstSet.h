#pragma once

#include <memory>

#include "../Interfaces/IVirtualSet.h"
#include "Sets/BooleanKeySet.h"
#include "Sets/FloatingPointKeySet.h"
#include "Sets/IntegralKeySet.h"
#include "Sets/PointerKeySet.h"
#include "Sets/StringKeySet.h"

namespace VirtualCollections {

    class VirtualConstSet : public IVirtualSet {
        std::unique_ptr<Sets::IBooleanKeySet>  _bools = std::make_unique<Sets::BooleanKeySet>();
        std::unique_ptr<Sets::IIntegralKeySet> _ints  = std::make_unique<Sets::IntegralKeySet>();
        std::unique_ptr<Sets::IFloatingPointKeySet> _floats =
            std::make_unique<Sets::FloatingPointKeySet>();
        std::unique_ptr<Sets::IStringKeySet>  _strings  = std::make_unique<Sets::StringKeySet>();
        std::unique_ptr<Sets::IPointerKeySet> _pointers = std::make_unique<Sets::PointerKeySet>();

    public:
        Sets::IBooleanKeySet*       bools() override { return _bools.get(); }
        Sets::IIntegralKeySet*      ints() override { return _ints.get(); }
        Sets::IFloatingPointKeySet* floats() override { return _floats.get(); }
        Sets::IStringKeySet*        strings() override { return _strings.get(); }
        Sets::IPointerKeySet*       pointers() override { return _pointers.get(); }

        const Sets::IBooleanKeySet*       bools() const override { return _bools.get(); }
        const Sets::IIntegralKeySet*      ints() const override { return _ints.get(); }
        const Sets::IFloatingPointKeySet* floats() const override { return _floats.get(); }
        const Sets::IStringKeySet*        strings() const override { return _strings.get(); }
        const Sets::IPointerKeySet*       pointers() const override { return _pointers.get(); }

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
