#pragma once

#include <type_traits>

#include "IVirtualCollection.h"

namespace VirtualCollections {

    struct IVirtualArray : public virtual IVirtualCollection {
        using ForEachIndexAndElementFn = IFunctionPointer<void(unsigned int, IVoidPointer*)>;

        template <typename T>
        class VirtualTypedArray {
            IVirtualArray* _array;
            bool           _destructable;

        public:
            class Iterator {
                VirtualTypedArray<T> _array;
                std::size_t          _index;

            public:
                Iterator(VirtualTypedArray<T> array, std::size_t index)
                    : _array(array), _index(index) {}
                T         operator*() const { return _array.at(_index); }
                Iterator& operator++() {
                    ++_index;
                    return *this;
                }
                bool operator==(const Iterator& other) const { return _index == other._index; }
                bool operator!=(const Iterator& other) const { return !(*this == other); }
            };

            Iterator begin() { return Iterator(*this, 0); }
            Iterator end() { return Iterator(*this, _array->size()); }

            VirtualTypedArray(IVirtualArray* array, bool destructable = false)
                : _array(array), _destructable(destructable) {}

            ~VirtualTypedArray() {
                if (_destructable) delete _array;
            }

            T operator[](unsigned int index) const { return _array->at<T>(index); }

            template <
                typename U = T, typename std::enable_if<!std::is_pointer<U>::value, bool>::type = 0>
            void push(T&& value) {
                _array->push<T>(std::forward<T>(value));
            }

            template <
                typename U = T, typename std::enable_if<std::is_pointer<U>::value, bool>::type = 0>
            void push(T pointer, bool destructable = true) {
                auto* element = new VoidPointer(pointer);
                if (!destructable) element->delete_rule()->disable_destruct_on_delete();
                _array->push_pointer(element);
            }

            void push(const char* value) { _array->push(value); }

            template <
                typename U = T, typename std::enable_if<!std::is_pointer<U>::value, bool>::type = 0>
            void insert(unsigned int index, T&& value) {
                _array->insert<T>(index, std::forward<T>(value));
            }

            template <
                typename U = T, typename std::enable_if<std::is_pointer<U>::value, bool>::type = 0>
            void insert(unsigned int index, T pointer, bool destructable = true) {
                _array->insert<T>(index, pointer, destructable);
            }

            void insert(unsigned int index, const char* value) { _array->insert(index, value); }

            template <typename... Args>
            void emplace(Args&&... args) {
                _array->push(new typename std::remove_pointer<T>::type(std::forward<Args>(args)...)
                );
            }

            T    first() const { return _array->first<T>(); }
            T    last() const { return _array->last<T>(); }
            T    at(unsigned int index) const { return _array->at<T>(index); }
            void erase(unsigned int index) { _array->erase(index); }
            void erase(unsigned int index, unsigned int count) { _array->erase(index, count); }
            unsigned int size() const { return _array->size(); }
            void         clear() { _array->clear(); }

            void foreach(std::function<void(T)> callback) {
                for (auto element : _array->iterable<T>()) callback(element);
            }

            void foreach(std::function<void(unsigned int, T)> callback) {
                unsigned int index = 0;
                for (auto element : _array->iterable<T>()) {
                    callback(index, element);
                    ++index;
                }
            }
        };

        class Iterator {
            IVirtualArray* _array;
            unsigned int   _index;

        public:
            Iterator(IVirtualArray* array, unsigned int index) : _array(array), _index(index) {}
            Iterator& operator++() {
                ++_index;
                return *this;
            }
            Iterator operator++(int) {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }
            bool          operator==(const Iterator& rhs) const { return _index == rhs._index; }
            bool          operator!=(const Iterator& rhs) const { return _index != rhs._index; }
            IVoidPointer* operator*() const { return _array->at(_index); }
        };

        template <typename T>
        class TemplatedIterator {
        private:
            IVirtualArray* _array;
            std::size_t    _index;

        public:
            TemplatedIterator(IVirtualArray* array, std::size_t index)
                : _array(array), _index(index) {}
            T                  operator*() const { return _array->template at<T>(_index); }
            TemplatedIterator& operator++() {
                ++_index;
                return *this;
            }
            bool operator==(const TemplatedIterator& other) const { return _index == other._index; }
            bool operator!=(const TemplatedIterator& other) const { return !(*this == other); }
        };

        template <typename T>
        class TemplatedIterable {
        private:
            IVirtualArray* _array;

        public:
            TemplatedIterable(IVirtualArray* array) : _array(array) {}
            TemplatedIterator<T> begin() { return TemplatedIterator<T>(_array, 0); }
            TemplatedIterator<T> end() { return TemplatedIterator<T>(_array, _array->size()); }
        };

        virtual ~IVirtualArray() = default;

        virtual IVoidPointer* at(unsigned int index) const = 0;
        virtual IVoidPointer* first() const                = 0;
        virtual IVoidPointer* last() const                 = 0;

        Iterator begin() { return Iterator(this, 0); }
        Iterator end() { return Iterator(this, this->size()); }

        template <typename T>
        TemplatedIterable<T> iterable() {
            return TemplatedIterable<T>(this);
        }

        template <typename T>
        VirtualTypedArray<T> typed(bool destructable = false) {
            return VirtualTypedArray<T>(this, destructable);
        }

        virtual void push_pointer(IVoidPointer*)                       = 0;
        virtual void insert_pointer(unsigned int index, IVoidPointer*) = 0;
        virtual void erase(unsigned int index)                         = 0;
        virtual void erase(unsigned int index, unsigned int count)     = 0;

        virtual void foreach(ForEachIndexAndElementFn*) const = 0;

        void foreach(std::function<void(unsigned int, IVoidPointer*)> callback) const {
            auto fn = unique_function_pointer(callback);
            this->foreach(fn.get());
        }

        void foreach(std::function<void(IVoidPointer*)> callback) const {
            auto fn = unique_function_pointer([callback](unsigned int, IVoidPointer* item) {
                callback(item);
            });
            this->foreach(fn.get());
        }

        template <typename T>
        void foreach(std::function<void(unsigned int, T)> callback) const {
            auto fn = unique_function_pointer([callback](unsigned int index, IVoidPointer* item) {
                callback(index, item->as<T>());
            });
            this->foreach(fn.get());
        }

        template <typename T>
        void foreach(std::function<void(T)> callback) const {
            auto fn = unique_function_pointer([callback](unsigned int, IVoidPointer* item) {
                callback(item->as<T>());
            });
            this->foreach(fn.get());
        }

        template <typename T, typename std::enable_if<!std::is_pointer<T>::value, int>::type = 0>
        T at(unsigned int index) const {
            if (auto* element = at(index)) return element->as<T>();
            return {};
        }

        template <typename T, typename std::enable_if<std::is_pointer<T>::value, int>::type = 0>
        T at(unsigned int index) const {
            auto* ptr = at(index);
            if (!ptr) return nullptr;
            return ptr->as<T>();
        }

        template <>
        const char* at<const char*>(unsigned int index) const {
            if (auto* element = this->at(index)) return element->as<const char*>();
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
            auto* element = new VoidPointer(value);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            this->push_pointer(element);
        }

        template <typename T>
        void push(T&& value) {
            auto* element = new VoidPointer(new T(std::forward<T>(value)));
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
            auto* element = new VoidPointer(value);
            if (!destructable) element->delete_rule()->disable_destruct_on_delete();
            this->insert_pointer(index, element);
        }

        template <typename T>
        void insert(unsigned int index, T&& value) {
            auto* element = new VoidPointer(new T(std::forward<T>(value)));
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
