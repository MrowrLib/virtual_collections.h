#pragma once

#include <void_pointer.h>

#include <type_traits>

#include "IVirtualCollection.h"

// TODO: add all of the contains() calls :)

namespace VirtualCollections {

    struct IVirtualMap : public virtual IVirtualCollection {
        virtual ~IVirtualMap() = default;

        struct IBooleanKeyMap : public IVirtualCollection {
            virtual ~IBooleanKeyMap()                                   = default;
            virtual void          insert(bool key, IVoidPointer* value) = 0;
            virtual IVoidPointer* get(bool key)                         = 0;
            virtual bool          contains(bool key)                    = 0;
            virtual void          remove(bool key)                      = 0;
        };

        struct IIntegralKeyMap : public IVirtualCollection {
            virtual ~IIntegralKeyMap()                                 = default;
            virtual void          insert(int key, IVoidPointer* value) = 0;
            virtual IVoidPointer* get(int key)                         = 0;
            virtual bool          contains(int key)                    = 0;
            virtual void          remove(int key)                      = 0;
        };

        struct IFloatingPointKeyMap : public IVirtualCollection {
            virtual ~IFloatingPointKeyMap()                               = default;
            virtual void          insert(double key, IVoidPointer* value) = 0;
            virtual IVoidPointer* get(double key)                         = 0;
            virtual bool          contains(double key)                    = 0;
            virtual void          remove(double key)                      = 0;
        };

        struct IStringKeyMap : public IVirtualCollection {
            virtual ~IStringKeyMap()                                           = default;
            virtual void          insert(const char* key, IVoidPointer* value) = 0;
            virtual IVoidPointer* get(const char* key)                         = 0;
            virtual bool          contains(const char* key)                    = 0;
            virtual void          remove(const char* key)                      = 0;
        };

        struct IPointerKeyMap : public IVirtualCollection {
            virtual ~IPointerKeyMap()                                    = default;
            virtual void          insert(void* key, IVoidPointer* value) = 0;
            virtual IVoidPointer* get(void* key)                         = 0;
            virtual bool          contains(void* key)                    = 0;
            virtual void          remove(void* key)                      = 0;
        };

        virtual IBooleanKeyMap*       bools()           = 0;
        virtual IIntegralKeyMap*      ints()            = 0;
        virtual IFloatingPointKeyMap* floating_points() = 0;
        virtual IStringKeyMap*        strings()         = 0;
        virtual IPointerKeyMap*       pointers()        = 0;

        /*
            Boolean Keys
        */

        // insert()

        template <
            typename TKey, typename TValue,
            std::enable_if_t<std::is_same<TKey, bool>::value, int> = 0>
        void insert(TKey key, TValue* value, bool destructable = true) {
            auto* element = new VoidPointer<TValue>(value);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            bools()->insert(key, element);
        }

        template <
            typename TKey, typename TValue,
            std::enable_if_t<std::is_same<TKey, bool>::value, int> = 0>
        void insert(TKey key, TValue&& value, bool destructable = true) {
            auto* element = new VoidPointer<TValue>(new TValue(std::forward<TValue>(value)));
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            bools()->insert(key, element);
        }

        // get()

        template <
            typename TValue,
            typename std::enable_if<!std::is_pointer<TValue>::value, int>::type = 0>
        TValue get(bool key) {
            return *bools()->get(key)->template as<TValue>();
        }

        template <
            typename TValue, typename std::enable_if<std::is_pointer<TValue>::value, int>::type = 0>
        TValue get(bool key) {
            auto ptr = bools()->get(key);
            if (!ptr) return nullptr;
            return static_cast<TValue>(ptr->void_ptr());
        }

        // TODO contains()

        /*
            Integral Keys
        */

        // insert()

        template <
            typename TKey, typename TValue,
            std::enable_if_t<
                std::conjunction<
                    std::is_integral<TKey>, std::negation<std::is_same<TKey, bool>>>::value,
                int> = 0>
        void insert(TKey key, TValue* value, bool destructable = true) {
            auto* element = new VoidPointer<TValue>(value);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            ints()->insert(key, element);
        }

        template <
            typename TKey, typename TValue,
            std::enable_if_t<
                std::conjunction<
                    std::is_integral<TKey>, std::negation<std::is_same<TKey, bool>>>::value,
                int> = 0>
        void insert(TKey key, TValue&& value, bool destructable = true) {
            auto* element = new VoidPointer<TValue>(new TValue(std::forward<TValue>(value)));
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            ints()->insert(key, element);
        }

        // get()

        template <
            typename TValue,
            typename std::enable_if<!std::is_pointer<TValue>::value, int>::type = 0>
        TValue get(int key) {
            return *ints()->get(key)->template as<TValue>();
        }

        template <
            typename TValue, typename std::enable_if<std::is_pointer<TValue>::value, int>::type = 0>
        TValue get(int key) {
            auto ptr = ints()->get(key);
            if (!ptr) return nullptr;
            return static_cast<TValue>(ptr->void_ptr());
        }

        /*
            Floating Point Keys
        */

        // insert()

        template <
            typename TKey, typename TValue,
            std::enable_if_t<std::is_floating_point<TKey>::value, int> = 0>
        void insert(TKey key, TValue* value, bool destructable = true) {
            auto* element = new VoidPointer<TValue>(value);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            floating_points()->insert(key, element);
        }

        template <
            typename TKey, typename TValue,
            std::enable_if_t<std::is_floating_point<TKey>::value, int> = 0>
        void insert(TKey key, TValue&& value, bool destructable = true) {
            auto* element = new VoidPointer<TValue>(new TValue(std::forward<TValue>(value)));
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            floating_points()->insert(key, element);
        }

        // get()

        template <
            typename TValue,
            typename std::enable_if<!std::is_pointer<TValue>::value, int>::type = 0>
        TValue get(double key) {
            return *floating_points()->get(key)->template as<TValue>();
        }

        template <
            typename TValue, typename std::enable_if<std::is_pointer<TValue>::value, int>::type = 0>
        TValue get(double key) {
            auto ptr = floating_points()->get(key);
            if (!ptr) return nullptr;
            return static_cast<TValue>(ptr->void_ptr());
        }

        /*
            String Keys
        */

        // insert()

        void insert(const char* key, const char* value, bool destructable = true) {
            char* copy = new char[strlen(value) + 1];
#ifdef _WIN32
            strcpy_s(copy, strlen(value) + 1, value);
#else
            strcpy(copy, value);
#endif
            auto* element = new VoidPointer<char>(copy);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            strings()->insert(key, element);
        }

        template <typename TValue>
        void insert(const char* key, TValue* value, bool destructable = true) {
            auto* element = new VoidPointer<TValue>(value);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            strings()->insert(key, element);
        }

        template <
            typename TKey, typename TValue,
            std::enable_if_t<
                !std::is_floating_point<TKey>::value && !std::is_integral<TKey>::value &&
                    !std::is_same<TKey, bool>::value,
                int> = 0>
        void insert(TKey key, TValue&& value, bool destructable = true) {
            auto* element = new VoidPointer<TValue>(new TValue(std::forward<TValue>(value)));
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            strings()->insert(key, element);
        }

        // get()

        template <
            typename TValue,
            typename std::enable_if<!std::is_pointer<TValue>::value, int>::type = 0>
        TValue get(const char* key) {
            return *strings()->get(key)->template as<TValue>();
        }

        template <
            typename TValue, typename std::enable_if<std::is_pointer<TValue>::value, int>::type = 0>
        TValue get(const char* key) {
            auto ptr = strings()->get(key);
            if (!ptr) return nullptr;
            return static_cast<TValue>(ptr->void_ptr());
        }

        /*
            Pointer Keys
        */

        // insert()

        template <
            typename TKey, typename TValue, std::enable_if_t<std::is_pointer<TKey>::value, int> = 0>
        void insert(TKey key, TValue* value, bool destructable = true) {
            auto* element = new VoidPointer<TValue>(value);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            pointers()->insert((void*)key, element);
        }

        // get()

        template <
            typename TKey, typename TValue,
            std::enable_if_t<std::is_pointer<TKey>::value && !std::is_pointer<TValue>::value, int> =
                0>
        TValue get(TKey key) {
            return *pointers()->get((void*)key)->template as<TValue>();
        }

        template <
            typename TKey, typename TValue,
            std::enable_if_t<std::is_pointer<TKey>::value && std::is_pointer<TValue>::value, int> =
                0>
        TValue get(TKey key) {
            auto ptr = pointers()->get((void*)key);
            if (!ptr) return nullptr;
            return static_cast<TValue>(ptr->void_ptr());
        }
    };
}
