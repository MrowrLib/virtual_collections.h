#pragma once

#include <memory>

#include "../Interfaces/IVirtualMap.h"
#include "Maps/BooleanKeyMap.h"
#include "Maps/FloatingPointKeyMap.h"
#include "Maps/IntegralKeyMap.h"
#include "Maps/PointerKeyMap.h"
#include "Maps/StringKeyMap.h"

namespace VirtualCollections {

    class VirtualMap : public IVirtualMap {
        std::unique_ptr<IBooleanKeyMap>       _bools    = nullptr;
        std::unique_ptr<IIntegralKeyMap>      _ints     = nullptr;
        std::unique_ptr<IFloatingPointKeyMap> _floats   = nullptr;
        std::unique_ptr<IStringKeyMap>        _strings  = nullptr;
        std::unique_ptr<IPointerKeyMap>       _pointers = nullptr;

    public:
        IBooleanKeyMap* bools() override {
            if (!_bools) _bools = std::make_unique<Maps::BooleanKeyMap>();
            return _bools.get();
        }

        IIntegralKeyMap* ints() override {
            if (!_ints) _ints = std::make_unique<Maps::IntegralKeyMap>();
            return _ints.get();
        }

        IFloatingPointKeyMap* floats() override {
            if (!_floats) _floats = std::make_unique<Maps::FloatingPointKeyMap>();
            return _floats.get();
        }

        IStringKeyMap* strings() override {
            if (!_strings) _strings = std::make_unique<Maps::StringKeyMap>();
            return _strings.get();
        }

        IPointerKeyMap* pointers() override {
            if (!_pointers) _pointers = std::make_unique<Maps::PointerKeyMap>();
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
