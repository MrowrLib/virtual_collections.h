#pragma once

#include <collections.h>

#include <string>

#include "../../Interfaces/IStringKeyMap.h"

namespace VirtualCollections::Maps {

    class StringKeyMap : public IStringKeyMap {
        collections_map<std::string, IVoidPointer*> _map;

    public:
        ~StringKeyMap() override {
            for (auto& pair : _map) delete pair.second;
        }

        unsigned int  size() const override { return _map.size(); }
        void          insert(const char* key, IVoidPointer* value) override { _map[key] = value; }
        IVoidPointer* get(const char* key) const override {
            auto it = _map.find(key);
            return it != _map.end() ? it->second : nullptr;
        }
        bool contains(const char* key) const override { return _map.find(key) != _map.end(); }
        void remove(const char* key) override { _map.erase(key); }
        void clear() override { _map.clear(); }
        void foreach_key_and_value(IVirtualCollection::ForEachElementFn* callback) const override {
            for (auto& pair : _map) {
                auto key = VoidPointer(new std::string(pair.first));
                callback->invoke(&key, pair.second);
            }
        }
        void foreach_value(IVirtualCollection::ForEachItemFn* callback) const override {
            for (auto& pair : _map) callback->invoke(pair.second);
        }
    };
}
