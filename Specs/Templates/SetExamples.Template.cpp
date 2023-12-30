#define SPEC_TEMPLATE Set_Examples

#include <virtual_collections/virtual_set.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Example("templated foreach") {
    std::vector<int> items;

    auto* set = current_test->var<IVirtualSet*>("set");

    set->insert(1);
    set->insert(2);
    set->insert(3);

    set->foreach<int>([&](int item) { items.push_back(item); });

    AssertThat(items, Has().Exactly(1).EqualTo(1));
    AssertThat(items, Has().Exactly(1).EqualTo(2));
    AssertThat(items, Has().Exactly(1).EqualTo(3));
}

Example("foreach IVoidPointer") {
    std::vector<int> items;

    auto* set = current_test->var<IVirtualSet*>("set");

    set->insert(1);
    set->insert(2);
    set->insert(3);

    set->foreach([&](IVoidPointer* item) { items.push_back(item->as<int>()); });

    AssertThat(items, Has().Exactly(1).EqualTo(1));
    AssertThat(items, Has().Exactly(1).EqualTo(2));
    AssertThat(items, Has().Exactly(1).EqualTo(3));
}

Example("boolean key set") {
    auto* set = current_test->var<IVirtualSet*>("set");

    AssertThat(set->bools()->size(), Equals(0));
    AssertThat(set->contains(true), IsFalse());
    set->insert(true);
    AssertThat(set->bools()->size(), Equals(1));
    AssertThat(set->contains(true), IsTrue());
}

Example("integer key set") {
    auto* set = current_test->var<IVirtualSet*>("set");

    AssertThat(set->ints()->size(), Equals(0));
    AssertThat(set->contains(123), IsFalse());
    set->insert(123);
    AssertThat(set->ints()->size(), Equals(1));
    AssertThat(set->contains(123), IsTrue());
}

Example("floating point key set") {
    auto* set = current_test->var<IVirtualSet*>("set");

    AssertThat(set->floats()->size(), Equals(0));
    AssertThat(set->contains(123.456), IsFalse());
    set->insert(123.456);
    AssertThat(set->floats()->size(), Equals(1));
    AssertThat(set->contains(123.456), IsTrue());
}

Example("string key set") {
    auto* set = current_test->var<IVirtualSet*>("set");

    AssertThat(set->strings()->size(), Equals(0));
    AssertThat(set->contains("hello"), IsFalse());
    set->insert("hello");
    AssertThat(set->strings()->size(), Equals(1));
    AssertThat(set->contains("hello"), IsTrue());
}

Example("pointer key set") {
    auto* set = current_test->var<IVirtualSet*>("set");

    auto  dog = std::make_shared<Dog>("Rover");
    auto* ptr = dog.get();

    AssertThat(set->pointers()->size(), Equals(0));
    AssertThat(set->contains(ptr), IsFalse());
    set->insert(ptr);
    AssertThat(set->pointers()->size(), Equals(1));
    AssertThat(set->contains(ptr), IsTrue());
}