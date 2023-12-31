#pragma once

#include <collections.h>

#include "../../Interfaces/IPointerKeySet.h"

namespace VirtualCollections::Sets {

    class PointerKeySet : public IPointerKeySet {
        collections_set<void*> _set;

    public:
        unsigned int size() const override { return _set.size(); }
        void         insert(void* key) override { _set.insert(key); }
        bool         contains(void* key) const override { return _set.find(key) != _set.end(); }
        void         erase(void* key) override { _set.erase(key); }
        void         clear() override { _set.clear(); }
        void foreach_key_and_value(IVirtualCollection::ForEachElementFn* callback) const override {
            for (auto& item : _set) {
                auto itemPtr = VoidPointer(new void*(item));
                callback->invoke(nullptr, &itemPtr);
            }
        }
        void foreach_value(IVirtualCollection::ForEachItemFn* callback) const override {
            for (auto& item : _set) {
                auto itemPtr = VoidPointer(new void*(item));
                callback->invoke(&itemPtr);
            }
        }
    };
}
