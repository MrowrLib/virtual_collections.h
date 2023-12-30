#pragma once

#include <memory>

#include "../Interfaces/IVirtualMap.h"
#include "Maps/BooleanKeyMap.h"
#include "Maps/FloatingPointKeyMap.h"
#include "Maps/IntegralKeyMap.h"
#include "Maps/PointerKeyMap.h"
#include "Maps/StringKeyMap.h"

namespace VirtualCollections {

    class VirtualConstMap : public IVirtualMap {
        std::unique_ptr<Maps::IBooleanKeyMap>  _bools = std::make_unique<Maps::BooleanKeyMap>();
        std::unique_ptr<Maps::IIntegralKeyMap> _ints  = std::make_unique<Maps::IntegralKeyMap>();
        std::unique_ptr<Maps::IFloatingPointKeyMap> _floats =
            std::make_unique<Maps::FloatingPointKeyMap>();
        std::unique_ptr<Maps::IStringKeyMap>  _strings  = std::make_unique<Maps::StringKeyMap>();
        std::unique_ptr<Maps::IPointerKeyMap> _pointers = std::make_unique<Maps::PointerKeyMap>();

    public:
        const Maps::IBooleanKeyMap*       bools() const override { return _bools.get(); }
        const Maps::IIntegralKeyMap*      ints() const override { return _ints.get(); }
        const Maps::IFloatingPointKeyMap* floats() const override { return _floats.get(); }
        const Maps::IStringKeyMap*        strings() const override { return _strings.get(); }
        const Maps::IPointerKeyMap*       pointers() const override { return _pointers.get(); }

        Maps::IBooleanKeyMap*       bools() override { return _bools.get(); }
        Maps::IIntegralKeyMap*      ints() override { return _ints.get(); }
        Maps::IFloatingPointKeyMap* floats() override { return _floats.get(); }
        Maps::IStringKeyMap*        strings() override { return _strings.get(); }
        Maps::IPointerKeyMap*       pointers() override { return _pointers.get(); }

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
