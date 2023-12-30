#pragma once

#include "IVirtualCollection.h"

namespace VirtualCollections::Sets {

    struct IBooleanKeySet : public IVirtualCollection {
        virtual ~IBooleanKeySet()             = default;
        virtual void insert(bool key)         = 0;
        virtual bool contains(bool key) const = 0;
        virtual void remove(bool key)         = 0;
    };
}
