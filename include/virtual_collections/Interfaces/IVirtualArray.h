#pragma once

#include <type_traits>

#include "IVirtualCollection.h"

namespace VirtualCollections {

    struct IVirtualArray : public virtual IVirtualCollection {
        using ForEachIndexAndElementFn = IFunctionPointer<void(unsigned int, IVoidPointer*)>;

        class Iterator {
            IVirtualArray* array;
            unsigned int   index;

        public:
            Iterator(IVirtualArray* array, unsigned int index) : array(array), index(index) {}

            Iterator& operator++() {
                ++index;
                return *this;
            }

            Iterator operator++(int) {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            bool operator==(const Iterator& rhs) const { return index == rhs.index; }

            bool operator!=(const Iterator& rhs) const { return index != rhs.index; }

            IVoidPointer* operator*() const { return array->pointer_at(index); }
        };

        virtual ~IVirtualArray() = default;

        virtual IVoidPointer* pointer_at(unsigned int index) const = 0;
        virtual IVoidPointer* first() const                        = 0;
        virtual IVoidPointer* last() const                         = 0;

        Iterator begin() { return Iterator(this, 0); }
        Iterator end() { return Iterator(this, this->size()); }

        virtual void push_pointer(IVoidPointer*)                       = 0;
        virtual void insert_pointer(unsigned int index, IVoidPointer*) = 0;
        virtual void erase(unsigned int index)                         = 0;
        virtual void erase(unsigned int index, unsigned int count)     = 0;

        virtual void foreach(ForEachIndexAndElementFn*) const = 0;

        void foreach(std::function<void(unsigned int, IVoidPointer*)> callback) const {
            auto fn = unique_function_pointer(callback);
            this->foreach(fn.get());
        }

        template <typename T, typename std::enable_if<!std::is_pointer<T>::value, int>::type = 0>
        T at(unsigned int index) const {
            if (auto* element = pointer_at(index)) return element->as<T>();
            return {};
        }

        template <typename T, typename std::enable_if<std::is_pointer<T>::value, int>::type = 0>
        T at(unsigned int index) const {
            auto* ptr = pointer_at(index);
            if (!ptr) return nullptr;
            return ptr->as<T>();
        }

        template <>
        const char* at<const char*>(unsigned int index) const {
            if (auto* element = this->pointer_at(index)) return element->as<const char*>();
            return "";
        }

        template <typename T, typename std::enable_if<!std::is_pointer<T>::value, int>::type = 0>
        T first() const {
            return first()->as<T>();
        }

        template <typename T, typename std::enable_if<std::is_pointer<T>::value, int>::type = 0>
        T first() const {
            return first()->as<T>();
        }

        template <typename T, typename std::enable_if<!std::is_pointer<T>::value, int>::type = 0>
        T last() const {
            return last()->as<T>();
        }

        template <typename T, typename std::enable_if<std::is_pointer<T>::value, int>::type = 0>
        T last() const {
            return last()->as<T>();
        }

        template <typename T>
        void push(T* value, bool destructable = true) {
            auto* element = new VoidPointer<T>(value);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            this->push_pointer(element);
        }

        template <typename T>
        void push(T&& value, bool destructable = true) {
            auto* element = new VoidPointer<T>(new T(std::forward<T>(value)));
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            this->push_pointer(element);
        }

        void push(const char* value) {
            char* copy = new char[strlen(value) + 1];
#ifdef _WIN32
            strcpy_s(copy, strlen(value) + 1, value);
#else
            strcpy(copy, value);
#endif
            this->push_pointer(new VoidPointer<char>(copy));
        }

        template <typename T>
        void insert(unsigned int index, T* value, bool destructable = true) {
            auto* element = new VoidPointer<T>(value);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            this->insert_pointer(index, element);
        }

        template <typename T>
        void insert(unsigned int index, T&& value, bool destructable = true) {
            auto* element = new VoidPointer<T>(new T(std::forward<T>(value)));
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            this->insert_pointer(index, element);
        }

        void insert(unsigned int index, const char* value) {
            char* copy = new char[strlen(value) + 1];
#ifdef _WIN32
            strcpy_s(copy, strlen(value) + 1, value);
#else
            strcpy(copy, value);
#endif
            this->insert_pointer(index, new VoidPointer<char>(copy));
        }
    };
}
