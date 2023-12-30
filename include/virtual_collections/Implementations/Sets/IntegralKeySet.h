#pragma once

#include <collections.h>

#include "../../Interfaces/IVirtualSet.h"

namespace VirtualCollections::Sets {

    class IntegralKeySet : public IVirtualSet::IIntegralKeySet {
        collections_set<int> _set;

    public:
        unsigned int size() const override { return _set.size(); }
        void         insert(int key) override { _set.insert(key); }
        bool         contains(int key) override { return _set.find(key) != _set.end(); }
        void         remove(int key) override { _set.erase(key); }
        void         clear() override { _set.clear(); }
        void foreach_key_and_value(IVirtualCollection::ForEachElementFn* callback) const override {
            for (auto& item : _set) {
                auto itemPtr = VoidPointer(new int(item));
                callback->invoke(nullptr, &itemPtr);
            }
        }
        void foreach_value(IVirtualCollection::ForEachItemFn* callback) const override {
            for (auto& item : _set) {
                auto itemPtr = VoidPointer(new int(item));
                callback->invoke(&itemPtr);
            }
        }
    };
}
