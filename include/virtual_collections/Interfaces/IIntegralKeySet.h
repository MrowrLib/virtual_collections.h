#pragma once

#include "IVirtualCollection.h"

namespace VirtualCollections::Sets {

    struct IIntegralKeySet : public IVirtualCollection {
        virtual ~IIntegralKeySet()           = default;
        virtual void insert(int key)         = 0;
        virtual bool contains(int key) const = 0;
        virtual void erase(int key)          = 0;
    };
}
