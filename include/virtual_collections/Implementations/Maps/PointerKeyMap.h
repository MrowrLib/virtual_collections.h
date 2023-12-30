#pragma once

#include <collections.h>

#include "../../Interfaces/IPointerKeyMap.h"

namespace VirtualCollections::Maps {

    class PointerKeyMap : public IPointerKeyMap {
        collections_map<void*, IVoidPointer*> _map;

    public:
        ~PointerKeyMap() override {
            for (auto& pair : _map) delete pair.second;
        }

        unsigned int  size() const override { return _map.size(); }
        void          insert(void* key, IVoidPointer* value) override { _map[key] = value; }
        IVoidPointer* get(void* key) const override {
            auto it = _map.find(key);
            return it != _map.end() ? it->second : nullptr;
        }
        bool contains(void* key) const override { return _map.find(key) != _map.end(); }
        void remove(void* key) override { _map.erase(key); }
        void clear() override { _map.clear(); }
        void foreach_key_and_value(IVirtualCollection::ForEachElementFn* callback) const override {
            for (auto& pair : _map) {
                auto key = VoidPointer(pair.first);
                callback->invoke(&key, pair.second);
            }
        }
        void foreach_value(IVirtualCollection::ForEachItemFn* callback) const override {
            for (auto& pair : _map) callback->invoke(pair.second);
        }
    };
}
