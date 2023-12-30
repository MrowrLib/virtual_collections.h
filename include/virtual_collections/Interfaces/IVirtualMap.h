#pragma once

#include <type_traits>

#include "IVirtualCollection.h"

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

        virtual IBooleanKeyMap*       bools()    = 0;
        virtual IIntegralKeyMap*      ints()     = 0;
        virtual IFloatingPointKeyMap* floats()   = 0;
        virtual IStringKeyMap*        strings()  = 0;
        virtual IPointerKeyMap*       pointers() = 0;

        /*
            Boolean Keys
        */

        // insert()

        template <
            typename TKey, typename TValue,
            std::enable_if_t<
                std::is_same<TKey, bool>::value && !std::is_floating_point<TKey>::value &&
                    !std::is_pointer<TKey>::value,
                int> = 0>
        void insert(TKey key, TValue* value, bool destructable = true) {
            auto* element = new VoidPointer(value);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            bools()->insert(key, element);
        }

        template <
            typename TKey, typename TValue,
            std::enable_if_t<
                std::is_same<TKey, bool>::value && !std::is_floating_point<TKey>::value &&
                    !std::is_pointer<TKey>::value,
                int> = 0>
        void insert(TKey key, TValue&& value, bool destructable = true) {
            auto* element = new VoidPointer(new TValue(std::forward<TValue>(value)));
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            bools()->insert(key, element);
        }

        template <
            typename TKey,
            std::enable_if_t<
                std::is_same<TKey, bool>::value && !std::is_floating_point<TKey>::value &&
                    !std::is_pointer<TKey>::value,
                int> = 0>
        void insert(TKey key, const char* value, bool destructable = true) {
            char* copy = new char[strlen(value) + 1];
#ifdef _WIN32
            strcpy_s(copy, strlen(value) + 1, value);
#else
            strcpy(copy, value);
#endif
            auto* element = new VoidPointer<char>(copy);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            bools()->insert(key, element);
        }

        template <
            typename TValue, typename TKey,
            std::enable_if_t<
                std::is_same<TKey, bool>::value && !std::is_floating_point<TKey>::value &&
                    !std::is_pointer<TKey>::value && !std::is_pointer<TValue>::value,
                int> = 0>
        TValue get(TKey key) {
            auto* ptr = bools()->get(key);
            if (!ptr) return {};
            return ptr->template as<TValue>();
        }

        template <
            typename TValue, typename TKey,
            std::enable_if_t<
                std::is_same<TKey, bool>::value && !std::is_pointer<TKey>::value &&
                    !std::is_floating_point<TKey>::value && std::is_pointer<TValue>::value,
                int> = 0>
        TValue get(TKey key) {
            auto* ptr = bools()->get(key);
            if (!ptr) return nullptr;
            return ptr->template as<TValue>();
        }

        // contains()

        bool contains(bool key) { return bools()->contains(key); }

        /*
            Integral Keys
        */

        // insert()

        template <
            typename TKey, typename TValue,
            std::enable_if_t<
                std::is_integral<TKey>::value && !std::is_same<TKey, bool>::value &&
                    !std::is_same<TValue, const char*>::value,
                int> = 0>
        void insert(TKey key, TValue* value, bool destructable = true) {
            auto* element = new VoidPointer(value);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            ints()->insert(key, element);
        }

        template <
            typename TKey, typename TValue,
            std::enable_if_t<
                std::is_integral<TKey>::value && !std::is_same<TKey, bool>::value &&
                    !std::is_pointer<TValue>::value,
                int> = 0>
        void insert(TKey key, TValue&& value, bool destructable = true) {
            auto* element = new VoidPointer(new TValue(std::forward<TValue>(value)));
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            ints()->insert(key, element);
        }

        template <
            typename TKey,
            std::enable_if_t<
                std::is_integral<TKey>::value && !std::is_same<TKey, bool>::value, int> = 0>
        void insert(TKey key, const char* value, bool destructable = true) {
            char* copy = new char[strlen(value) + 1];
#ifdef _WIN32
            strcpy_s(copy, strlen(value) + 1, value);
#else
            strcpy(copy, value);
#endif
            auto* element = new VoidPointer<char>(copy);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            ints()->insert(key, element);
        }

        // get()

        template <
            typename TValue, typename TKey,
            std::enable_if_t<
                std::is_integral<TKey>::value && !std::is_same<TKey, bool>::value &&
                    !std::is_pointer<TValue>::value,
                int> = 0>
        TValue get(TKey key) {
            auto* ptr = ints()->get(key);
            if (!ptr) return {};
            return ptr->template as<TValue>();
        }

        template <
            typename TValue, typename TKey,
            std::enable_if_t<
                std::is_integral<TKey>::value && !std::is_same<TKey, bool>::value &&
                    std::is_pointer<TValue>::value,
                int> = 0>
        TValue get(TKey key) {
            auto* ptr = ints()->get(key);
            if (!ptr) return nullptr;
            return ptr->template as<TValue>();
        }

        // contains()

        template <
            typename T,
            std::enable_if_t<
                std::conjunction<std::is_integral<T>, std::negation<std::is_same<T, bool>>>::value,
                int> = 0>
        bool contains(T key) {
            return ints()->contains(key);
        }

        /*
            Floating Point Keys
        */

        // insert()

        template <
            typename TKey, typename TValue,
            std::enable_if_t<
                std::is_floating_point<TKey>::value && !std::is_same<TKey, bool>::value &&
                    !std::is_same<TValue, const char*>::value,
                int> = 0>
        void insert(TKey key, TValue* value, bool destructable = true) {
            auto* element = new VoidPointer(value);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            floats()->insert(key, element);
        }

        template <
            typename TKey, typename TValue,
            std::enable_if_t<
                std::is_floating_point<TKey>::value && !std::is_same<TKey, bool>::value &&
                    !std::is_pointer<TValue>::value,
                int> = 0>
        void insert(TKey key, TValue&& value, bool destructable = true) {
            auto* element = new VoidPointer(new TValue(std::forward<TValue>(value)));
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            floats()->insert(key, element);
        }

        template <
            typename TKey,
            std::enable_if_t<
                std::is_floating_point<TKey>::value && !std::is_same<TKey, bool>::value, int> = 0>
        void insert(TKey key, const char* value, bool destructable = true) {
            char* copy = new char[strlen(value) + 1];
#ifdef _WIN32
            strcpy_s(copy, strlen(value) + 1, value);
#else
            strcpy(copy, value);
#endif
            auto* element = new VoidPointer<char>(copy);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            floats()->insert(key, element);
        }

        // get()

        template <
            typename TValue, typename TKey,
            std::enable_if_t<
                std::is_floating_point<TKey>::value && !std::is_same<TKey, bool>::value &&
                    !std::is_pointer<TValue>::value,
                int> = 0>
        TValue get(TKey key) {
            auto* ptr = floats()->get(key);
            if (!ptr) return {};
            return ptr->template as<TValue>();
        }

        template <
            typename TValue, typename TKey,
            std::enable_if_t<
                std::is_floating_point<TKey>::value && !std::is_same<TKey, bool>::value &&
                    std::is_pointer<TValue>::value,
                int> = 0>
        TValue get(TKey key) {
            auto* ptr = floats()->get(key);
            if (!ptr) return nullptr;
            return ptr->template as<TValue>();
        }

        // contains()

        template <typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
        bool contains(T key) {
            return floats()->contains(key);
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
            auto* element = new VoidPointer(value);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            strings()->insert(key, element);
        }

        template <typename TValue>
        void insert(const char* key, TValue&& value, bool destructable = true) {
            auto* element = new VoidPointer(new TValue(std::forward<TValue>(value)));
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            strings()->insert(key, element);
        }

        // get()

        template <typename TValue, std::enable_if_t<!std::is_pointer<TValue>::value, int> = 0>
        TValue get(const char* key) {
            auto* ptr = strings()->get(key);
            if (!ptr) return {};
            return ptr->template as<TValue>();
        }

        template <typename TValue, std::enable_if_t<std::is_pointer<TValue>::value, int> = 0>
        TValue get(const char* key) {
            auto* ptr = strings()->get(key);
            if (!ptr) return nullptr;
            return ptr->template as<TValue>();
        }

        // contains()

        bool contains(const char* key) { return strings()->contains(key); }

        /*
            Pointer Keys
        */

        // insert()

        template <
            typename TKey, typename TValue, std::enable_if_t<std::is_pointer<TKey>::value, int> = 0>
        void insert(TKey key, TValue* value, bool destructable = true) {
            auto* element = new VoidPointer(value);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            pointers()->insert(key, element);
        }

        template <
            typename TKey, typename TValue, std::enable_if_t<std::is_pointer<TKey>::value, int> = 0>
        void insert(TKey key, TValue&& value, bool destructable = true) {
            auto* element = new VoidPointer(new TValue(std::forward<TValue>(value)));
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            pointers()->insert(key, element);
        }

        template <typename TKey, std::enable_if_t<std::is_pointer<TKey>::value, int> = 0>
        void insert(TKey key, const char* value, bool destructable = true) {
            char* copy = new char[strlen(value) + 1];
#ifdef _WIN32
            strcpy_s(copy, strlen(value) + 1, value);
#else
            strcpy(copy, value);
#endif
            auto* element = new VoidPointer<char>(copy);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            pointers()->insert(key, element);
        }

        // get()

        template <
            typename TValue, typename TKey,
            std::enable_if_t<std::is_pointer<TKey>::value && !std::is_pointer<TValue>::value, int> =
                0>
        TValue get(TKey key) {
            auto* ptr = pointers()->get(key);
            if (!ptr) return {};
            return ptr->template as<TValue>();
        }

        template <
            typename TValue, typename TKey,
            std::enable_if_t<std::is_pointer<TKey>::value && std::is_pointer<TValue>::value, int> =
                0>
        TValue get(TKey key) {
            auto* ptr = pointers()->get(key);
            if (!ptr) return nullptr;
            return ptr->as<TValue>();
        }

        // contains()

        template <typename T, std::enable_if_t<std::is_pointer<T>::value, int> = 0>
        bool contains(T key) {
            return pointers()->contains((void*)key);
        }
    };
}
