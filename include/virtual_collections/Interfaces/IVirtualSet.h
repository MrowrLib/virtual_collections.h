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

        template <typename T, std::enable_if_t<std::is_same<T, bool>::value, int> = 0>
        void insert(T value, bool destructable = true) {
            bools()->insert(value);
        }

        // contains()

        template <typename T, std::enable_if_t<std::is_same<T, bool>::value, int> = 0>
        bool contains(T value) {
            return bools()->contains(value);
        }

        /*
            Integral Keys
        */

        // insert()

        template <
            typename T,
            std::enable_if_t<
                std::conjunction<std::is_integral<T>, std::negation<std::is_same<T, bool>>>::value,
                int> = 0>
        void insert(T value) {
            ints()->insert(value);
        }

        // contains()

        template <
            typename T,
            std::enable_if_t<
                std::conjunction<std::is_integral<T>, std::negation<std::is_same<T, bool>>>::value,
                int> = 0>
        bool contains(T value) {
            return ints()->contains(value);
        }

        /*
            Floating Point Keys
        */

        // insert()

        template <typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
        void insert(T value) {
            floats()->insert(value);
        }

        // contains()

        template <typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
        bool contains(T value) {
            return floats()->contains(value);
        }

        /*
            String Keys
        */

        // insert()

        void insert(const char* value) { strings()->insert(value); }

        // contains()

        bool contains(const char* value) { return strings()->contains(value); }

        /*
            Pointer Keys
        */

        // insert()

        template <typename T, typename std::enable_if<std::is_pointer<T>::value, int>::type = 0>
        void insert(T value) {
            pointers()->insert(value);
        }

        // contains()

        template <typename T, typename std::enable_if<std::is_pointer<T>::value, int>::type = 0>
        bool contains(T value) {
            return pointers()->contains(value);
        }
    };
}
