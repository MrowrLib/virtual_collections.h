#pragma once

#include <memory>

#include "../Interfaces/IVirtualMap.h"
#include "Maps/BooleanKeyMap.h"
#include "Maps/FloatingPointKeyMap.h"
#include "Maps/IntegralKeyMap.h"
#include "Maps/PointerKeyMap.h"
#include "Maps/StringKeyMap.h"

namespace VirtualCollections {

    class VirtualLazyMap : public IVirtualMap {
        std::unique_ptr<Maps::IBooleanKeyMap>       _bools    = nullptr;
        std::unique_ptr<Maps::IIntegralKeyMap>      _ints     = nullptr;
        std::unique_ptr<Maps::IFloatingPointKeyMap> _floats   = nullptr;
        std::unique_ptr<Maps::IStringKeyMap>        _strings  = nullptr;
        std::unique_ptr<Maps::IPointerKeyMap>       _pointers = nullptr;

    public:
        Maps::IBooleanKeyMap* bools() override {
            if (!_bools) _bools = std::make_unique<Maps::BooleanKeyMap>();
            return _bools.get();
        }
        Maps::IIntegralKeyMap* ints() override {
            if (!_ints) _ints = std::make_unique<Maps::IntegralKeyMap>();
            return _ints.get();
        }
        Maps::IFloatingPointKeyMap* floats() override {
            if (!_floats) _floats = std::make_unique<Maps::FloatingPointKeyMap>();
            return _floats.get();
        }
        Maps::IStringKeyMap* strings() override {
            if (!_strings) _strings = std::make_unique<Maps::StringKeyMap>();
            return _strings.get();
        }
        Maps::IPointerKeyMap* pointers() override {
            if (!_pointers) _pointers = std::make_unique<Maps::PointerKeyMap>();
            return _pointers.get();
        }

        const Maps::IBooleanKeyMap* bools() const override {
            if (_bools) return _bools.get();
            else return nullptr;
        }
        const Maps::IIntegralKeyMap* ints() const override {
            if (_ints) return _ints.get();
            else return nullptr;
        }
        const Maps::IFloatingPointKeyMap* floats() const override {
            if (_floats) return _floats.get();
            else return nullptr;
        }
        const Maps::IStringKeyMap* strings() const override {
            if (_strings) return _strings.get();
            else return nullptr;
        }
        const Maps::IPointerKeyMap* pointers() const override {
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
