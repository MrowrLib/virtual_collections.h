#define SPEC_GROUP VirtualArray

#include <virtual_collections/array.h>

#include <memory>

#include "SpecHelper.h"  // IWYU pragma: keep

Example("usage example") {
    auto array = std::unique_ptr<IVirtualArray>(new VirtualArray());
    AssertThat(array->size(), Equals(0));
    AssertThat(array->get<const char*>(0), Equals(""));

    array->push(123);
    AssertThat(array->size(), Equals(1));
    AssertThat(array->get<int>(0), Equals(123));

    array->push("Hello, world!");
    AssertThat(array->size(), Equals(2));
    AssertThat(array->get<int>(0), Equals(123));
    AssertThat(array->get<const char*>(1), Equals("Hello, world!"));

    array->insert(0, "First!");
    AssertThat(array->size(), Equals(3));
    AssertThat(array->get<const char*>(0), Equals("First!"));
    AssertThat(array->get<int>(1), Equals(123));
    AssertThat(array->get<const char*>(2), Equals("Hello, world!"));
}
