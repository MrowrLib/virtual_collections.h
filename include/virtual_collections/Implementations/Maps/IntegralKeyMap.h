#pragma once

#include <collections.h>

#include "../../Interfaces/IVirtualMap.h"

namespace VirtualCollections::Maps {

    class IntegralKeyMap : public IVirtualMap::IIntegralKeyMap {
        collections_map<int, IVoidPointer*> _map;

    public:
        ~IntegralKeyMap() override {
            for (auto& pair : _map) delete pair.second;
        }

        unsigned int  size() const override { return _map.size(); }
        void          insert(int key, IVoidPointer* value) override { _map[key] = value; }
        IVoidPointer* get(int key) override {
            auto it = _map.find(key);
            return it != _map.end() ? it->second : nullptr;
        }
        bool contains(int key) override { return _map.find(key) != _map.end(); }
        void remove(int key) override { _map.erase(key); }
        void clear() override { _map.clear(); }
        void foreach_element(IVirtualCollection::ForEachElementFn* callback) const override {
            for (auto& pair : _map) {
                auto key = VoidPointer(new int(pair.first));
                callback->invoke(&key, pair.second);
            }
        }
        void foreach_item(IVirtualCollection::ForEachItemFn* callback) const override {
            for (auto& pair : _map) callback->invoke(pair.second);
        }
    };
}
