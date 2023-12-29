#pragma once

#include <function_pointer.h>
#include <void_pointer.h>

#include <functional>

namespace VirtualCollections {

    struct IVirtualCollection {
        using ForEachItemFn    = IFunctionPointer<void(IVoidPointer*)>;
        using ForEachElementFn = IFunctionPointer<void(IVoidPointer*, IVoidPointer*)>;

        virtual ~IVirtualCollection() = default;

        virtual unsigned int size() const                             = 0;
        virtual void         foreach_element(ForEachElementFn*) const = 0;
        virtual void         foreach_item(ForEachItemFn*) const       = 0;
        virtual void         clear()                                  = 0;

        void foreach(std::function<void(IVoidPointer*)> callback) const {
            auto fn = unique_function_pointer(callback);
            this->foreach_item(fn.get());
        }

        void foreach(std::function<void(IVoidPointer*, IVoidPointer*)> callback) const {
            auto fn = unique_function_pointer(callback);
            this->foreach_element(fn.get());
        }
    };
}
