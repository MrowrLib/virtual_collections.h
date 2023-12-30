#pragma once

#include <collections.h>

#include "../../Interfaces/IVirtualMap.h"

namespace VirtualCollections::Maps {

    class BooleanKeyMap : public IVirtualMap::IBooleanKeyMap {
        collections_map<bool, IVoidPointer*> _map;

    public:
        ~BooleanKeyMap() override {
            for (auto& pair : _map) delete pair.second;
        }

        unsigned int  size() const override { return _map.size(); }
        void          insert(bool key, IVoidPointer* value) override { _map[key] = value; }
        IVoidPointer* get(bool key) override {
            auto it = _map.find(key);
            return it != _map.end() ? it->second : nullptr;
        }
        bool contains(bool key) override { return _map.find(key) != _map.end(); }
        void remove(bool key) override { _map.erase(key); }
        void clear() override { _map.clear(); }
        void foreach_key_and_value(IVirtualCollection::ForEachElementFn* callback) const override {
            for (auto& pair : _map) {
                auto key = VoidPointer(new bool(pair.first));
                callback->invoke(&key, pair.second);
            }
        }
        void foreach_value(IVirtualCollection::ForEachItemFn* callback) const override {
            for (auto& pair : _map) callback->invoke(pair.second);
        }
    };
}
