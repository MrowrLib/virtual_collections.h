#pragma once

#include <type_traits>

#include "IBooleanKeyMap.h"
#include "IFloatingPointKeyMap.h"
#include "IIntegralKeyMap.h"
#include "IPointerKeyMap.h"
#include "IStringKeyMap.h"
#include "IVirtualCollection.h"

namespace VirtualCollections {

    struct IVirtualMap : public virtual IVirtualCollection {
        virtual ~IVirtualMap() = default;

        virtual Maps::IBooleanKeyMap*       bools()    = 0;
        virtual Maps::IIntegralKeyMap*      ints()     = 0;
        virtual Maps::IFloatingPointKeyMap* floats()   = 0;
        virtual Maps::IStringKeyMap*        strings()  = 0;
        virtual Maps::IPointerKeyMap*       pointers() = 0;

        virtual const Maps::IBooleanKeyMap*       bools() const    = 0;
        virtual const Maps::IIntegralKeyMap*      ints() const     = 0;
        virtual const Maps::IFloatingPointKeyMap* floats() const   = 0;
        virtual const Maps::IStringKeyMap*        strings() const  = 0;
        virtual const Maps::IPointerKeyMap*       pointers() const = 0;

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

        // erase()

        template <
            typename TKey,
            std::enable_if_t<
                std::is_same<TKey, bool>::value && !std::is_floating_point<TKey>::value &&
                    !std::is_pointer<TKey>::value,
                int> = 0>
        void erase(TKey key) {
            bools()->erase(key);
        }

        // get()

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
                std::is_same<TKey, bool>::value && !std::is_floating_point<TKey>::value &&
                    !std::is_pointer<TKey>::value && !std::is_pointer<TValue>::value,
                int> = 0>
        TValue get(TKey key) const {
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

        template <
            typename TValue, typename TKey,
            std::enable_if_t<
                std::is_same<TKey, bool>::value && !std::is_pointer<TKey>::value &&
                    !std::is_floating_point<TKey>::value && std::is_pointer<TValue>::value,
                int> = 0>
        TValue get(TKey key) const {
            auto* ptr = bools()->get(key);
            if (!ptr) return nullptr;
            return ptr->template as<TValue>();
        }

        // contains()

        bool contains(bool key) { return bools()->contains(key); }
        bool contains(bool key) const { return bools()->contains(key); }

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

        // erase()

        template <
            typename TKey,
            std::enable_if_t<
                std::is_integral<TKey>::value && !std::is_same<TKey, bool>::value, int> = 0>
        void erase(TKey key) {
            ints()->erase(key);
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
                    !std::is_pointer<TValue>::value,
                int> = 0>
        TValue get(TKey key) const {
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

        template <
            typename TValue, typename TKey,
            std::enable_if_t<
                std::is_integral<TKey>::value && !std::is_same<TKey, bool>::value &&
                    std::is_pointer<TValue>::value,
                int> = 0>
        TValue get(TKey key) const {
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

        template <
            typename T,
            std::enable_if_t<
                std::conjunction<std::is_integral<T>, std::negation<std::is_same<T, bool>>>::value,
                int> = 0>
        bool contains(T key) const {
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

        // erase()

        template <
            typename TKey,
            std::enable_if_t<
                std::is_floating_point<TKey>::value && !std::is_same<TKey, bool>::value, int> = 0>
        void erase(TKey key) {
            floats()->erase(key);
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
                    !std::is_pointer<TValue>::value,
                int> = 0>
        TValue get(TKey key) const {
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

        template <
            typename TValue, typename TKey,
            std::enable_if_t<
                std::is_floating_point<TKey>::value && !std::is_same<TKey, bool>::value &&
                    std::is_pointer<TValue>::value,
                int> = 0>
        TValue get(TKey key) const {
            auto* ptr = floats()->get(key);
            if (!ptr) return nullptr;
            return ptr->template as<TValue>();
        }

        // contains()

        template <typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
        bool contains(T key) {
            return floats()->contains(key);
        }

        template <typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
        bool contains(T key) const {
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

        // erase()

        void erase(const char* key) { strings()->erase(key); }

        // get()

        template <typename TValue, std::enable_if_t<!std::is_pointer<TValue>::value, int> = 0>
        TValue get(const char* key) {
            auto* ptr = strings()->get(key);
            if (!ptr) return {};
            return ptr->template as<TValue>();
        }

        template <typename TValue, std::enable_if_t<!std::is_pointer<TValue>::value, int> = 0>
        TValue get(const char* key) const {
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

        template <typename TValue, std::enable_if_t<std::is_pointer<TValue>::value, int> = 0>
        TValue get(const char* key) const {
            auto* ptr = strings()->get(key);
            if (!ptr) return nullptr;
            return ptr->template as<TValue>();
        }

        // contains()

        bool contains(const char* key) { return strings()->contains(key); }
        bool contains(const char* key) const { return strings()->contains(key); }

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

        // erase()

        template <typename TKey, std::enable_if_t<std::is_pointer<TKey>::value, int> = 0>
        void erase(TKey key) {
            pointers()->erase(key);
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
            std::enable_if_t<std::is_pointer<TKey>::value && !std::is_pointer<TValue>::value, int> =
                0>
        TValue get(TKey key) const {
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
            return ptr->template as<TValue>();
        }

        template <
            typename TValue, typename TKey,
            std::enable_if_t<std::is_pointer<TKey>::value && std::is_pointer<TValue>::value, int> =
                0>
        TValue get(TKey key) const {
            auto* ptr = pointers()->get(key);
            if (!ptr) return nullptr;
            return ptr->template as<TValue>();
        }

        // contains()

        template <typename T, std::enable_if_t<std::is_pointer<T>::value, int> = 0>
        bool contains(T key) {
            return pointers()->contains((void*)key);
        }

        template <typename T, std::enable_if_t<std::is_pointer<T>::value, int> = 0>
        bool contains(T key) const {
            return pointers()->contains((void*)key);
        }
    };
}
