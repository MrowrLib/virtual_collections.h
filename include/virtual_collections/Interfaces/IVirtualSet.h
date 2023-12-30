#pragma once

#include "IBooleanKeySet.h"
#include "IFloatingPointKeySet.h"
#include "IIntegralKeySet.h"
#include "IPointerKeySet.h"
#include "IStringKeySet.h"
#include "IVirtualCollection.h"

namespace VirtualCollections {

    struct IVirtualSet : public IVirtualCollection {
        virtual ~IVirtualSet() = default;

        virtual Sets::IBooleanKeySet*       bools()    = 0;
        virtual Sets::IIntegralKeySet*      ints()     = 0;
        virtual Sets::IFloatingPointKeySet* floats()   = 0;
        virtual Sets::IStringKeySet*        strings()  = 0;
        virtual Sets::IPointerKeySet*       pointers() = 0;

        virtual const Sets::IBooleanKeySet*       bools() const    = 0;
        virtual const Sets::IIntegralKeySet*      ints() const     = 0;
        virtual const Sets::IFloatingPointKeySet* floats() const   = 0;
        virtual const Sets::IStringKeySet*        strings() const  = 0;
        virtual const Sets::IPointerKeySet*       pointers() const = 0;

        /*
          Boolean Keys
        */

        // insert()

        template <
            typename TKey,
            std::enable_if_t<
                std::is_same<TKey, bool>::value && !std::is_floating_point<TKey>::value &&
                    !std::is_pointer<TKey>::value,
                int> = 0>
        void insert(TKey key) {
            bools()->insert(key);
        }

        // erasae()

        template <
            typename TKey,
            std::enable_if_t<
                std::is_same<TKey, bool>::value && !std::is_floating_point<TKey>::value &&
                    !std::is_pointer<TKey>::value,
                int> = 0>
        void erase(TKey key) {
            bools()->erase(key);
        }

        // contains()

        bool contains(bool key) { return bools()->contains(key); }
        bool contains(bool key) const { return bools()->contains(key); }

        /*
            Integral Keys
        */

        // insert()

        template <
            typename TKey,
            std::enable_if_t<
                std::is_integral<TKey>::value && !std::is_same<TKey, bool>::value, int> = 0>
        void insert(TKey key) {
            ints()->insert(key);
        }

        // erase()

        template <
            typename TKey,
            std::enable_if_t<
                std::is_integral<TKey>::value && !std::is_same<TKey, bool>::value, int> = 0>
        void erase(TKey key) {
            ints()->erase(key);
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
            typename TKey,
            std::enable_if_t<
                std::is_floating_point<TKey>::value && !std::is_same<TKey, bool>::value, int> = 0>
        void insert(TKey key) {
            floats()->insert(key);
        }

        // erase()

        template <
            typename TKey,
            std::enable_if_t<
                std::is_floating_point<TKey>::value && !std::is_same<TKey, bool>::value, int> = 0>
        void erase(TKey key) {
            floats()->erase(key);
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

        void insert(const char* key) { strings()->insert(key); }

        // erase()

        void erase(const char* key) { strings()->erase(key); }

        // contains()

        bool contains(const char* key) { return strings()->contains(key); }
        bool contains(const char* key) const { return strings()->contains(key); }

        /*
            Pointer Keys
        */

        // insert()

        template <typename TKey, std::enable_if_t<std::is_pointer<TKey>::value, int> = 0>
        void insert(TKey key) {
            pointers()->insert(key);
        }

        // erase()

        template <typename TKey, std::enable_if_t<std::is_pointer<TKey>::value, int> = 0>
        void erase(TKey key) {
            pointers()->erase(key);
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
