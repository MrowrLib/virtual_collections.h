#pragma once

#include "IVirtualCollection.h"

namespace VirtualCollections::Maps {

    struct IBooleanKeyMap : public IVirtualCollection {
        virtual ~IBooleanKeyMap()                                   = default;
        virtual void          insert(bool key, IVoidPointer* value) = 0;
        virtual IVoidPointer* get(bool key) const                   = 0;
        virtual bool          contains(bool key) const              = 0;
        virtual void          erase(bool key)                       = 0;
    };
}
