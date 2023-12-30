#pragma once

#include "IVirtualCollection.h"

namespace VirtualCollections::Sets {

    struct IStringKeySet : public IVirtualCollection {
        virtual ~IStringKeySet()                     = default;
        virtual void insert(const char* key)         = 0;
        virtual bool contains(const char* key) const = 0;
        virtual void erase(const char* key)          = 0;
    };
}
