#define SPEC_TEMPLATE Array_Examples

// TODO: test memory management via: erase(i), erase(i, count), clear(), destructor

#include <virtual_collections/virtual_array.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Example("templated foreach element") {
    _Log_("Example...");

    std::vector<int> items;

    auto* array = current_test->var<IVirtualArray*>("array");

    array->push(1);
    array->push(2);
    array->push(3);

    array->foreach<int>([&](int item) { items.push_back(item); });

    AssertThat(items[0], Equals(1));
    AssertThat(items[1], Equals(2));
    AssertThat(items[2], Equals(3));
}

Example("templated foreach element with index") {
    std::vector<int>          items;
    std::vector<unsigned int> indexes;

    auto* array = current_test->var<IVirtualArray*>("array");

    array->push(1);
    array->push(2);
    array->push(3);

    array->foreach<int>([&](unsigned int index, int item) {
        indexes.push_back(index);
        items.push_back(item);
    });

    AssertThat(indexes[0], Equals(0));
    AssertThat(indexes[1], Equals(1));
    AssertThat(indexes[2], Equals(2));

    AssertThat(items[0], Equals(1));
    AssertThat(items[1], Equals(2));
    AssertThat(items[2], Equals(3));
}

Example("foreach IVoidPointer") {
    std::vector<int> items;

    auto* array = current_test->var<IVirtualArray*>("array");

    array->push(1);
    array->push(2);
    array->push(3);

    array->foreach([&](IVoidPointer* item) { items.push_back(item->as<int>()); });

    AssertThat(items[0], Equals(1));
    AssertThat(items[1], Equals(2));
    AssertThat(items[2], Equals(3));
}

Example("foreach IVoidPointer with index") {
    std::vector<int>          items;
    std::vector<unsigned int> indexes;

    auto* array = current_test->var<IVirtualArray*>("array");

    array->push(1);
    array->push(2);
    array->push(3);

    array->foreach([&](unsigned int index, IVoidPointer* item) {
        indexes.push_back(index);
        items.push_back(item->as<int>());
    });

    AssertThat(indexes[0], Equals(0));
    AssertThat(indexes[1], Equals(1));
    AssertThat(indexes[2], Equals(2));

    AssertThat(items[0], Equals(1));
    AssertThat(items[1], Equals(2));
    AssertThat(items[2], Equals(3));
}

Example("range based for loop") {
    std::vector<IVoidPointer*> values;

    auto* array = current_test->var<IVirtualArray*>("array");

    array->push(123);
    array->push(456);
    array->push(789);

    for (auto* element : *array) values.push_back(element);

    AssertThat(values.size(), Equals(3));
    AssertThat(values[0]->as<int>(), Equals(123));
    AssertThat(values[1]->as<int>(), Equals(456));
    AssertThat(values[2]->as<int>(), Equals(789));
}

Example("templated range based loop") {
    std::vector<int> values;

    auto* array = current_test->var<IVirtualArray*>("array");

    array->push(123);
    array->push(456);
    array->push(789);

    for (auto element : array->iterable<int>()) values.push_back(element);

    AssertThat(values.size(), Equals(3));
    AssertThat(values[0], Equals(123));
    AssertThat(values[1], Equals(456));
    AssertThat(values[2], Equals(789));
}

Example("range based loop over pointers") {
    std::vector<Dog*> values;

    auto* array = current_test->var<IVirtualArray*>("array");

    array->push(new Dog("Fido"));
    array->push(new Dog("Rex"));
    array->push(new Dog("Spot"));

    for (auto* dog : array->iterable<Dog*>()) values.push_back(dog);

    AssertThat(values.size(), Equals(3));
    AssertThat(values[0]->name(), Equals("Fido"));
    AssertThat(values[1]->name(), Equals("Rex"));
    AssertThat(values[2]->name(), Equals("Spot"));
}

Example("boolean value array") {
    auto* array = current_test->var<IVirtualArray*>("array");

    // push() and at() and size()
    AssertThat(array->size(), Equals(0));
    AssertThat(array->at<bool>(0), Equals(false));  // Default value
    array->push(true);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->at<bool>(0), Equals(true));

    // insert()
    array->insert(0, false);
    AssertThat(array->size(), Equals(2));
    AssertThat(array->at<bool>(0), Equals(false));
    AssertThat(array->at<bool>(1), Equals(true));

    // first and last
    AssertThat(array->first<bool>(), Equals(false));
    AssertThat(array->last<bool>(), Equals(true));

    // erase
    array->erase(0);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->at<bool>(0), Equals(true));
}

Example("integer value array") {
    auto* array = current_test->var<IVirtualArray*>("array");

    // push() and at() and size()
    AssertThat(array->size(), Equals(0));
    AssertThat(array->at<int>(0), Equals(0));  // Default value
    array->push(123);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->at<int>(0), Equals(123));

    // insert()
    array->insert(0, 456);
    AssertThat(array->size(), Equals(2));
    AssertThat(array->at<int>(0), Equals(456));
    AssertThat(array->at<int>(1), Equals(123));

    // first and last
    AssertThat(array->first<int>(), Equals(456));
    AssertThat(array->last<int>(), Equals(123));

    // erase
    array->erase(0);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->at<int>(0), Equals(123));
}

Example("floating point value array") {
    auto* array = current_test->var<IVirtualArray*>("array");

    // push() and at() and size()
    AssertThat(array->size(), Equals(0));
    AssertThat(array->at<float>(0), Equals(0.0f));  // Default value
    array->push(123.456f);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->at<float>(0), Equals(123.456f));

    // insert()
    array->insert(0, 456.789f);
    AssertThat(array->size(), Equals(2));
    AssertThat(array->at<float>(0), Equals(456.789f));
    AssertThat(array->at<float>(1), Equals(123.456f));

    // first and last
    AssertThat(array->first<float>(), Equals(456.789f));
    AssertThat(array->last<float>(), Equals(123.456f));

    // erase
    array->erase(0);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->at<float>(0), Equals(123.456f));
}

Example("string value array") {
    auto* array = current_test->var<IVirtualArray*>("array");

    std::string str{"Hello"};

    // push() and at() and size()
    AssertThat(array->size(), Equals(0));
    AssertThat(array->at<const char*>(0), Equals(""));  // Default value
    // array->push("Hello");
    array->push(str.c_str());
    AssertThat(array->size(), Equals(1));
    AssertThat(array->at<const char*>(0), Equals("Hello"));

    // insert()
    array->insert(0, "World");
    AssertThat(array->size(), Equals(2));
    AssertThat(array->at<const char*>(0), Equals("World"));
    AssertThat(array->at<const char*>(1), Equals("Hello"));

    // first and last
    AssertThat(array->first<const char*>(), Equals("World"));
    AssertThat(array->last<const char*>(), Equals("Hello"));

    // erase
    array->erase(0);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->at<const char*>(0), Equals("Hello"));
}

Example("pointer value array") {
    auto* array = current_test->var<IVirtualArray*>("array");

    // push() and at() and size()
    AssertThat(array->size(), Equals(0));
    AssertThat(array->at<Dog*>(0), Equals(nullptr));  // Default value
    array->push(new Dog("Fido"));
    AssertThat(array->size(), Equals(1));
    AssertThat(array->at<Dog*>(0)->name(), Equals("Fido"));

    // insert()
    array->insert(0, new Dog("Rex"));
    AssertThat(array->size(), Equals(2));
    AssertThat(array->at<Dog*>(0)->name(), Equals("Rex"));
    AssertThat(array->at<Dog*>(1)->name(), Equals("Fido"));

    // first and last
    AssertThat(array->first<Dog*>()->name(), Equals("Rex"));
    AssertThat(array->last<Dog*>()->name(), Equals("Fido"));

    // erase
    array->erase(0);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->at<Dog*>(0)->name(), Equals("Fido"));
}