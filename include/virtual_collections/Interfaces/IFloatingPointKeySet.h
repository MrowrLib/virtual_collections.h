#pragma once

#include "IVirtualCollection.h"

namespace VirtualCollections::Sets {

    struct IFloatingPointKeySet : public IVirtualCollection {
        virtual ~IFloatingPointKeySet()         = default;
        virtual void insert(double key)         = 0;
        virtual bool contains(double key) const = 0;
        virtual void remove(double key)         = 0;
    };
}
