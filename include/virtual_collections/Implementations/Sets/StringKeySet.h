#pragma once

#include <collections.h>

#include <string>

#include "../../Interfaces/IVirtualSet.h"

namespace VirtualCollections::Sets {

    class StringKeySet : public IVirtualSet::IStringKeySet {
        collections_set<std::string> _set;

    public:
        unsigned int size() const override { return _set.size(); }
        void         insert(const char* key) override { _set.insert(key); }
        bool         contains(const char* key) override { return _set.find(key) != _set.end(); }
        void         remove(const char* key) override { _set.erase(key); }
        void         clear() override { _set.clear(); }
        void foreach_key_and_value(IVirtualCollection::ForEachElementFn* callback) const override {
            for (auto& item : _set) {
                auto itemPtr = VoidPointer(new std::string(item));
                callback->invoke(nullptr, &itemPtr);
            }
        }
        void foreach_value(IVirtualCollection::ForEachItemFn* callback) const override {
            for (auto& item : _set) {
                auto itemPtr = VoidPointer(new std::string(item));
                callback->invoke(&itemPtr);
            }
        }
    };
}
