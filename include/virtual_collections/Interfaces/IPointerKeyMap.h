#pragma once

#include "IVirtualCollection.h"

namespace VirtualCollections::Maps {

    struct IPointerKeyMap : public IVirtualCollection {
        virtual ~IPointerKeyMap()                                    = default;
        virtual void          insert(void* key, IVoidPointer* value) = 0;
        virtual IVoidPointer* get(void* key) const                   = 0;
        virtual bool          contains(void* key) const              = 0;
        virtual void          remove(void* key)                      = 0;
    };
}
