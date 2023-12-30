#pragma once

#include "IVirtualCollection.h"

namespace VirtualCollections::Maps {

    struct IFloatingPointKeyMap : public IVirtualCollection {
        virtual ~IFloatingPointKeyMap()                               = default;
        virtual void          insert(double key, IVoidPointer* value) = 0;
        virtual IVoidPointer* get(double key) const                   = 0;
        virtual bool          contains(double key) const              = 0;
        virtual void          erase(double key)                       = 0;
    };
}
