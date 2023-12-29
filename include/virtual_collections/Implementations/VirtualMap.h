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
        std::unique_ptr<Maps::BooleanKeyMap>       _boolean_key_map        = nullptr;
        std::unique_ptr<Maps::IntegralKeyMap>      _integral_key_map       = nullptr;
        std::unique_ptr<Maps::FloatingPointKeyMap> _floating_point_key_map = nullptr;
        std::unique_ptr<Maps::StringKeyMap>        _string_key_map         = nullptr;
        std::unique_ptr<Maps::PointerKeyMap>       _pointer_key_map        = nullptr;

    public:
        Maps::BooleanKeyMap* bools() override {
            if (!_boolean_key_map) _boolean_key_map = std::make_unique<Maps::BooleanKeyMap>();
            return _boolean_key_map.get();
        }

        Maps::IntegralKeyMap* ints() override {
            if (!_integral_key_map) _integral_key_map = std::make_unique<Maps::IntegralKeyMap>();
            return _integral_key_map.get();
        }

        Maps::FloatingPointKeyMap* floating_points() override {
            if (!_floating_point_key_map)
                _floating_point_key_map = std::make_unique<Maps::FloatingPointKeyMap>();
            return _floating_point_key_map.get();
        }

        Maps::StringKeyMap* strings() override {
            if (!_string_key_map) _string_key_map = std::make_unique<Maps::StringKeyMap>();
            return _string_key_map.get();
        }

        Maps::PointerKeyMap* pointers() override {
            if (!_pointer_key_map) _pointer_key_map = std::make_unique<Maps::PointerKeyMap>();
            return _pointer_key_map.get();
        }

        unsigned int size() const override {
            return (_boolean_key_map ? _boolean_key_map->size() : 0) +
                   (_integral_key_map ? _integral_key_map->size() : 0) +
                   (_floating_point_key_map ? _floating_point_key_map->size() : 0) +
                   (_string_key_map ? _string_key_map->size() : 0) +
                   (_pointer_key_map ? _pointer_key_map->size() : 0);
        }

        void foreach_element(ForEachElementFn* callback) const override {
            if (_boolean_key_map) _boolean_key_map->foreach_element(callback);
            if (_integral_key_map) _integral_key_map->foreach_element(callback);
            if (_floating_point_key_map) _floating_point_key_map->foreach_element(callback);
            if (_string_key_map) _string_key_map->foreach_element(callback);
            if (_pointer_key_map) _pointer_key_map->foreach_element(callback);
        }

        void foreach_item(ForEachItemFn* callback) const override {
            if (_boolean_key_map) _boolean_key_map->foreach_item(callback);
            if (_integral_key_map) _integral_key_map->foreach_item(callback);
            if (_floating_point_key_map) _floating_point_key_map->foreach_item(callback);
            if (_string_key_map) _string_key_map->foreach_item(callback);
            if (_pointer_key_map) _pointer_key_map->foreach_item(callback);
        }

        void clear() override {
            if (_boolean_key_map) _boolean_key_map->clear();
            if (_integral_key_map) _integral_key_map->clear();
            if (_floating_point_key_map) _floating_point_key_map->clear();
            if (_string_key_map) _string_key_map->clear();
            if (_pointer_key_map) _pointer_key_map->clear();
        }
    };
}
