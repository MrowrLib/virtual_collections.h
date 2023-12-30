#pragma once

#include "IVirtualCollection.h"

namespace VirtualCollections::Maps {

    struct IIntegralKeyMap : public IVirtualCollection {
        virtual ~IIntegralKeyMap()                                 = default;
        virtual void          insert(int key, IVoidPointer* value) = 0;
        virtual IVoidPointer* get(int key) const                   = 0;
        virtual bool          contains(int key) const              = 0;
        virtual void          remove(int key)                      = 0;
    };
}
