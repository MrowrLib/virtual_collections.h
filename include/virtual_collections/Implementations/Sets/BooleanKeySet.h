#pragma once

#include <collections.h>

#include "../../Interfaces/IVirtualSet.h"

namespace VirtualCollections::Sets {

    class BooleanKeySet : public IBooleanKeySet {
        collections_set<bool> _set;

    public:
        unsigned int size() const override { return _set.size(); }
        void         insert(bool key) override { _set.insert(key); }
        bool         contains(bool key) const override { return _set.find(key) != _set.end(); }
        void         remove(bool key) override { _set.erase(key); }
        void         clear() override { _set.clear(); }
        void foreach_key_and_value(IVirtualCollection::ForEachElementFn* callback) const override {
            for (auto item : _set) {
                auto itemPtr = VoidPointer(new bool(item));
                callback->invoke(nullptr, &itemPtr);
            }
        }
        void foreach_value(IVirtualCollection::ForEachItemFn* callback) const override {
            for (auto item : _set) {
                auto itemPtr = VoidPointer(new bool(item));
                callback->invoke(&itemPtr);
            }
        }
    };
}
