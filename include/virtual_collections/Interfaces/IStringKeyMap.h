#pragma once

#include "IVirtualCollection.h"

namespace VirtualCollections::Maps {

    struct IStringKeyMap : public IVirtualCollection {
        virtual ~IStringKeyMap()                                           = default;
        virtual void          insert(const char* key, IVoidPointer* value) = 0;
        virtual IVoidPointer* get(const char* key) const                   = 0;
        virtual bool          contains(const char* key) const              = 0;
        virtual void          remove(const char* key)                      = 0;
    };
}
