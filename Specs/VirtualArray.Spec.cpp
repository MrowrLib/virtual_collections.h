#define SPEC_GROUP VirtualArray

#include <virtual_collections/array.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Example("boolean value array") {
    auto array = std::unique_ptr<IVirtualArray>(new VirtualArray());

    // push() and get() and size()
    AssertThat(array->size(), Equals(0));
    AssertThat(array->get<bool>(0), Equals(false));  // Default value
    array->push(true);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->get<bool>(0), Equals(true));

    // insert()
    array->insert(0, false);
    AssertThat(array->size(), Equals(2));
    AssertThat(array->get<bool>(0), Equals(false));
    AssertThat(array->get<bool>(1), Equals(true));

    // first and last
    AssertThat(array->first<bool>(), Equals(false));
    AssertThat(array->last<bool>(), Equals(true));

    // remove
    array->remove(0);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->get<bool>(0), Equals(true));
}

Example("integer value array") {
    auto array = std::unique_ptr<IVirtualArray>(new VirtualArray());

    // push() and get() and size()
    AssertThat(array->size(), Equals(0));
    AssertThat(array->get<int>(0), Equals(0));  // Default value
    array->push(123);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->get<int>(0), Equals(123));

    // insert()
    array->insert(0, 456);
    AssertThat(array->size(), Equals(2));
    AssertThat(array->get<int>(0), Equals(456));
    AssertThat(array->get<int>(1), Equals(123));

    // first and last
    AssertThat(array->first<int>(), Equals(456));
    AssertThat(array->last<int>(), Equals(123));

    // remove
    array->remove(0);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->get<int>(0), Equals(123));
}

Example("floating point value array") {
    auto array = std::unique_ptr<IVirtualArray>(new VirtualArray());

    // push() and get() and size()
    AssertThat(array->size(), Equals(0));
    AssertThat(array->get<float>(0), Equals(0.0f));  // Default value
    array->push(123.456f);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->get<float>(0), Equals(123.456f));

    // insert()
    array->insert(0, 456.789f);
    AssertThat(array->size(), Equals(2));
    AssertThat(array->get<float>(0), Equals(456.789f));
    AssertThat(array->get<float>(1), Equals(123.456f));

    // first and last
    AssertThat(array->first<float>(), Equals(456.789f));
    AssertThat(array->last<float>(), Equals(123.456f));

    // remove
    array->remove(0);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->get<float>(0), Equals(123.456f));
}

Example("string value array") {
    auto array = std::unique_ptr<IVirtualArray>(new VirtualArray());

    // push() and get() and size()
    AssertThat(array->size(), Equals(0));
    AssertThat(array->get<const char*>(0), Equals(""));  // Default value
    array->push("Hello");
    AssertThat(array->size(), Equals(1));
    AssertThat(array->get<const char*>(0), Equals("Hello"));

    // insert()
    array->insert(0, "World");
    AssertThat(array->size(), Equals(2));
    AssertThat(array->get<const char*>(0), Equals("World"));
    AssertThat(array->get<const char*>(1), Equals("Hello"));

    // first and last
    AssertThat(array->first<const char*>(), Equals("World"));
    AssertThat(array->last<const char*>(), Equals("Hello"));

    // remove
    array->remove(0);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->get<const char*>(0), Equals("Hello"));
}

Example("pointer value array") {
    auto array = std::unique_ptr<IVirtualArray>(new VirtualArray());

    // push() and get() and size()
    AssertThat(array->size(), Equals(0));
    AssertThat(array->get<Dog*>(0), Equals(nullptr));  // Default value
    array->push(new Dog("Fido"));
    AssertThat(array->size(), Equals(1));
    AssertThat(array->get<Dog*>(0)->name(), Equals("Fido"));

    // insert()
    array->insert(0, new Dog("Rex"));
    AssertThat(array->size(), Equals(2));
    AssertThat(array->get<Dog*>(0)->name(), Equals("Rex"));
    AssertThat(array->get<Dog*>(1)->name(), Equals("Fido"));

    // first and last
    AssertThat(array->first<Dog*>()->name(), Equals("Rex"));
    AssertThat(array->last<Dog*>()->name(), Equals("Fido"));

    // remove
    array->remove(0);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->get<Dog*>(0)->name(), Equals("Fido"));
}
