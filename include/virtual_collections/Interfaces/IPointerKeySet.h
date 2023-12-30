#pragma once

#include "IVirtualCollection.h"

namespace VirtualCollections::Sets {

    struct IPointerKeySet : public IVirtualCollection {
        virtual ~IPointerKeySet()              = default;
        virtual void insert(void* key)         = 0;
        virtual bool contains(void* key) const = 0;
        virtual void remove(void* key)         = 0;
    };
}
