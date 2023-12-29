#pragma once

#include "IVirtualCollection.h"
namespace VirtualCollections {

    struct IVirtualSet : public IVirtualCollection {
        virtual ~IVirtualSet() = default;

        struct IBooleanKeySet : public IVirtualCollection {
            virtual ~IBooleanKeySet()       = default;
            virtual void insert(bool key)   = 0;
            virtual bool contains(bool key) = 0;
            virtual void remove(bool key)   = 0;
        };

        struct IIntegralKeySet : public IVirtualCollection {
            virtual ~IIntegralKeySet()     = default;
            virtual void insert(int key)   = 0;
            virtual bool contains(int key) = 0;
            virtual void remove(int key)   = 0;
        };

        struct IFloatingPointKeySet : public IVirtualCollection {
            virtual ~IFloatingPointKeySet()   = default;
            virtual void insert(double key)   = 0;
            virtual bool contains(double key) = 0;
            virtual void remove(double key)   = 0;
        };

        struct IStringKeySet : public IVirtualCollection {
            virtual ~IStringKeySet()               = default;
            virtual void insert(const char* key)   = 0;
            virtual bool contains(const char* key) = 0;
            virtual void remove(const char* key)   = 0;
        };

        struct IPointerKeySet : public IVirtualCollection {
            virtual ~IPointerKeySet()        = default;
            virtual void insert(void* key)   = 0;
            virtual bool contains(void* key) = 0;
            virtual void remove(void* key)   = 0;
        };

        virtual IBooleanKeySet*       bools()    = 0;
        virtual IIntegralKeySet*      ints()     = 0;
        virtual IFloatingPointKeySet* floats()   = 0;
        virtual IStringKeySet*        strings()  = 0;
        virtual IPointerKeySet*       pointers() = 0;

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

        // contains()

        bool contains(bool key) { return bools()->contains(key); }

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
            typename TKey,
            std::enable_if_t<
                std::is_floating_point<TKey>::value && !std::is_same<TKey, bool>::value, int> = 0>
        void insert(TKey key) {
            floats()->insert(key);
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

        void insert(const char* key) { strings()->insert(key); }

        // contains()

        bool contains(const char* key) { return strings()->contains(key); }

        /*
            Pointer Keys
        */

        // insert()

        template <typename TKey, std::enable_if_t<std::is_pointer<TKey>::value, int> = 0>
        void insert(TKey key) {
            pointers()->insert(key);
        }

        // contains()

        template <typename T, std::enable_if_t<std::is_pointer<T>::value, int> = 0>
        bool contains(T key) {
            return pointers()->contains((void*)key);
        }
    };
}
