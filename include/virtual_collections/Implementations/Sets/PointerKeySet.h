#pragma once

#include <collections.h>

#include "../../Interfaces/IVirtualSet.h"

namespace VirtualCollections::Sets {

    class PointerKeySet : public IVirtualSet::IPointerKeySet {
        collections_set<void*> _set;

    public:
        unsigned int size() const override { return _set.size(); }
        void         insert(void* key) override { _set.insert(key); }
        bool         contains(void* key) override { return _set.find(key) != _set.end(); }
        void         remove(void* key) override { _set.erase(key); }
        void         clear() override { _set.clear(); }
        void foreach_element(IVirtualCollection::ForEachElementFn* callback) const override {
            for (auto& item : _set) {
                auto itemPtr = VoidPointer(new void*(item));
                callback->invoke(nullptr, &itemPtr);
            }
        }
        void foreach_item(IVirtualCollection::ForEachItemFn* callback) const override {
            for (auto& item : _set) {
                auto itemPtr = VoidPointer(new void*(item));
                callback->invoke(&itemPtr);
            }
        }
    };
}
