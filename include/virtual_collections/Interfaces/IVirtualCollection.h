#pragma once

#include <function_pointer.h>
#include <void_pointer/deprecated.h>

#include <functional>

namespace VirtualCollections {

    struct IVirtualCollection {
        using ForEachItemFn    = IFunctionPointer<void(IVoidPointer*)>;
        using ForEachElementFn = IFunctionPointer<void(IVoidPointer*, IVoidPointer*)>;

        virtual ~IVirtualCollection() = default;

        virtual unsigned int size() const                                   = 0;
        virtual void         foreach_key_and_value(ForEachElementFn*) const = 0;
        virtual void         foreach_value(ForEachItemFn*) const            = 0;
        virtual void         clear()                                        = 0;

        void foreach(std::function<void(IVoidPointer*)> callback) const {
            auto fn = unique_function_pointer(callback);
            this->foreach_value(fn.get());
        }

        void foreach(std::function<void(IVoidPointer*, IVoidPointer*)> callback) const {
            auto fn = unique_function_pointer(callback);
            this->foreach_key_and_value(fn.get());
        }

        template <typename T>
        void foreach(std::function<void(T)> callback) const {
            auto fn = unique_function_pointer([callback](IVoidPointer* item) {
                callback(item->as<T>());
            });
            this->foreach_value(fn.get());
        }

        template <typename T>
        void foreach(std::function<void(T, IVoidPointer*)> callback) const {
            auto fn = unique_function_pointer([callback](IVoidPointer* key, IVoidPointer* item) {
                callback(key->as<T>(), item);
            });
            this->foreach_key_and_value(fn.get());
        }

        template <typename TKey, typename TValue>
        void foreach(std::function<void(TKey, TValue)> callback) const {
            auto fn = unique_function_pointer([callback](IVoidPointer* key, IVoidPointer* item) {
                callback(key->as<TKey>(), item->as<TValue>());
            });
            this->foreach_key_and_value(fn.get());
        }
    };
}
