#pragma once

#include <collections.h>

#include "../../Interfaces/IVirtualSet.h"

namespace VirtualCollections::Sets {

    class FloatingPointKeySet : public IVirtualSet::IFloatingPointKeySet {
        collections_set<double> _set;

    public:
        unsigned int size() const override { return _set.size(); }
        void         insert(double key) override { _set.insert(key); }
        bool         contains(double key) override { return _set.find(key) != _set.end(); }
        void         remove(double key) override { _set.erase(key); }
        void         clear() override { _set.clear(); }
        void foreach_element(IVirtualCollection::ForEachElementFn* callback) const override {
            for (auto& item : _set) {
                auto itemPtr = VoidPointer(new double(item));
                callback->invoke(nullptr, &itemPtr);
            }
        }
        void foreach_item(IVirtualCollection::ForEachItemFn* callback) const override {
            for (auto& item : _set) {
                auto itemPtr = VoidPointer(new double(item));
                callback->invoke(&itemPtr);
            }
        }
    };
}