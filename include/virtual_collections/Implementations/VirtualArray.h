#pragma once

#include <vector>

#include "../Interfaces/IVirtualArray.h"

namespace VirtualCollections {

    class VirtualArray : public IVirtualArray {
        std::vector<IVoidPointer*> _elements;

    public:
        ~VirtualArray() override {
            for (auto& element : _elements) delete element;
        }

        unsigned int size() const override { return _elements.size(); }

        void foreach_key_and_value(ForEachElementFn* callback) const override {
            for (size_t i = 0; i < _elements.size(); ++i) {
                auto indexPtr = VoidPointer(new unsigned int(i));
                callback->invoke(&indexPtr, _elements[i]);
            }
        }

        void foreach_value(ForEachItemFn* callback) const override {
            for (auto& element : _elements) callback->invoke(element);
        }

        void foreach(ForEachIndexAndElementFn* callback) const override {
            for (size_t i = 0; i < _elements.size(); ++i) callback->invoke(i, _elements[i]);
        }

        IVoidPointer* at(unsigned int index) const override {
            if (index < _elements.size()) return _elements[index];
            return nullptr;
        }

        IVoidPointer* first() const override {
            if (!_elements.empty()) return _elements.front();
            return nullptr;
        }

        IVoidPointer* last() const override {
            if (!_elements.empty()) return _elements.back();
            return nullptr;
        }

        void push_pointer(IVoidPointer* element) override { _elements.push_back(element); }

        void insert_pointer(unsigned int index, IVoidPointer* element) override {
            if (index < _elements.size()) _elements.insert(_elements.begin() + index, element);
            else _elements.push_back(element);
        }

        void erase(unsigned int index) override {
            if (index < _elements.size()) {
                delete _elements[index];
                _elements.erase(_elements.begin() + index);
            }
        }

        void erase(unsigned int index, unsigned int count) override {
            if (index < _elements.size()) {
                for (unsigned int i = 0; i < count; ++i) delete _elements[index + i];
                _elements.erase(_elements.begin() + index, _elements.begin() + index + count);
            }
        }

        void clear() override {
            for (auto& element : _elements) delete element;
            _elements.clear();
        }
    };
}
