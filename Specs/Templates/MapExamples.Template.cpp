#define SPEC_TEMPLATE Map_Examples

#include <virtual_collections/virtual_map.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Example("templated foreach") {
    std::vector<int>    keys;
    std::vector<double> values;

    auto* map = current_test->var<IVirtualMap*>("map");

    map->insert(123, 456.789);
    map->insert(456, 123.456);

    map->foreach<int, double>([&](int key, double value) {
        keys.push_back(key);
        values.push_back(value);
    });

    AssertThat(keys[0], Equals(123));
    AssertThat(keys[1], Equals(456));

    AssertThat(values[0], Equals(456.789));
    AssertThat(values[1], Equals(123.456));
}

Example("templated foreach only key type") {
    std::vector<int>    keys;
    std::vector<double> values;

    auto* map = current_test->var<IVirtualMap*>("map");

    map->insert(123, 456.789);
    map->insert(456, 123.456);

    map->foreach<int>([&](int key, IVoidPointer* value) {
        keys.push_back(key);
        values.push_back(value->as<double>());
    });

    AssertThat(keys[0], Equals(123));
    AssertThat(keys[1], Equals(456));

    AssertThat(values[0], Equals(456.789));
    AssertThat(values[1], Equals(123.456));
}

Example("foreach IVoidPointer") {
    std::vector<int>    keys;
    std::vector<double> values;

    auto* map = current_test->var<IVirtualMap*>("map");

    map->insert(123, 456.789);
    map->insert(456, 123.456);

    map->foreach([&](IVoidPointer* key, IVoidPointer* value) {
        keys.push_back(key->as<int>());
        values.push_back(value->as<double>());
    });

    AssertThat(keys[0], Equals(123));
    AssertThat(keys[1], Equals(456));

    AssertThat(values[0], Equals(456.789));
    AssertThat(values[1], Equals(123.456));
}

Example("boolean key map") {
    auto* map = current_test->var<IVirtualMap*>("map");

    // Value Type
    AssertThat(map->bools()->size(), Equals(0));
    AssertThat(map->contains(true), IsFalse());
    map->insert(true, 123);
    AssertThat(map->bools()->size(), Equals(1));
    AssertThat(map->contains(true), IsTrue());
    AssertThat(map->get<int>(true), Equals(123));

    // Pointer Type
    map->clear();
    AssertThat(map->bools()->size(), Equals(0));
    AssertThat(map->contains(false), IsFalse());
    map->insert(false, new Dog("Rover"));
    AssertThat(map->bools()->size(), Equals(1));
    AssertThat(map->contains(false), IsTrue());
    AssertThat(map->get<Dog*>(false)->name(), Equals("Rover"));

    // String type
    map->clear();
    AssertThat(map->bools()->size(), Equals(0));
    AssertThat(map->contains(true), IsFalse());
    map->insert(true, "hello");
    AssertThat(map->bools()->size(), Equals(1));
    AssertThat(map->contains(true), IsTrue());
    AssertThat(map->get<const char*>(true), Equals("hello"));
}

Example("integer key map") {
    auto* map = current_test->var<IVirtualMap*>("map");

    // Value Type
    AssertThat(map->ints()->size(), Equals(0));
    AssertThat(map->contains(123), IsFalse());
    map->insert(123, 456);
    AssertThat(map->ints()->size(), Equals(1));
    AssertThat(map->contains(123), IsTrue());
    AssertThat(map->get<int>(123), Equals(456));

    // Pointer Type
    map->clear();
    AssertThat(map->ints()->size(), Equals(0));
    AssertThat(map->contains(456), IsFalse());
    map->insert(456, new Dog("Rover"));
    AssertThat(map->ints()->size(), Equals(1));
    AssertThat(map->contains(456), IsTrue());
    AssertThat(map->get<Dog*>(456)->name(), Equals("Rover"));

    // String type
    map->clear();
    AssertThat(map->ints()->size(), Equals(0));
    AssertThat(map->contains(123), IsFalse());
    map->insert(123, "hello");
    AssertThat(map->ints()->size(), Equals(1));
    AssertThat(map->contains(123), IsTrue());
    AssertThat(map->get<const char*>(123), Equals("hello"));
}

Example("floating point key map") {
    auto* map = current_test->var<IVirtualMap*>("map");

    // Value Type
    AssertThat(map->floats()->size(), Equals(0));
    AssertThat(map->contains(123.456), IsFalse());
    map->insert(123.456, 456.789);
    AssertThat(map->floats()->size(), Equals(1));
    AssertThat(map->contains(123.456), IsTrue());
    AssertThat(map->get<double>(123.456), Equals(456.789));

    // Pointer Type
    AssertThat(map->floats()->size(), Equals(1));
    AssertThat(map->contains(456.789), IsFalse());
    map->insert(456.789, new Dog("Rover"));
    AssertThat(map->floats()->size(), Equals(2));
    AssertThat(map->contains(456.789), IsTrue());
    AssertThat(map->get<Dog*>(456.789)->name(), Equals("Rover"));

    // String type
    map->clear();
    AssertThat(map->floats()->size(), Equals(0));
    AssertThat(map->contains(123.456), IsFalse());
    map->insert(123.456, "hello");
    AssertThat(map->floats()->size(), Equals(1));
    AssertThat(map->contains(123.456), IsTrue());
    AssertThat(map->get<const char*>(123.456), Equals("hello"));
}

Example("string key map") {
    auto* map = current_test->var<IVirtualMap*>("map");

    // Value Type
    AssertThat(map->strings()->size(), Equals(0));
    AssertThat(map->contains("hello"), IsFalse());
    map->insert("hello", 123);
    AssertThat(map->strings()->size(), Equals(1));
    AssertThat(map->contains("hello"), IsTrue());
    AssertThat(map->get<int>("hello"), Equals(123));

    // Pointer Type
    map->clear();
    AssertThat(map->strings()->size(), Equals(0));
    AssertThat(map->contains("hello"), IsFalse());
    map->insert("hello", new Dog("Rover"));
    AssertThat(map->strings()->size(), Equals(1));
    AssertThat(map->contains("hello"), IsTrue());
    AssertThat(map->get<Dog*>("hello")->name(), Equals("Rover"));

    // String type
    map->clear();
    AssertThat(map->strings()->size(), Equals(0));
    AssertThat(map->contains("hello"), IsFalse());
    map->insert("hello", "world");
    AssertThat(map->strings()->size(), Equals(1));
    AssertThat(map->contains("hello"), IsTrue());
    AssertThat(map->get<const char*>("hello"), Equals("world"));
}

Example("pointer key map") {
    auto* map = current_test->var<IVirtualMap*>("map");

    auto  dog = std::unique_ptr<Dog>(new Dog("Rover"));
    auto* ptr = dog.get();

    // Value Type
    AssertThat(map->pointers()->size(), Equals(0));
    AssertThat(map->contains(ptr), IsFalse());
    map->insert(ptr, 123);
    AssertThat(map->pointers()->size(), Equals(1));
    AssertThat(map->contains(ptr), IsTrue());
    AssertThat(map->get<int>(ptr), Equals(123));

    // Pointer Type
    map->clear();
    AssertThat(map->pointers()->size(), Equals(0));
    AssertThat(map->contains(ptr), IsFalse());
    map->insert(ptr, new Dog("Rover"));
    AssertThat(map->pointers()->size(), Equals(1));
    AssertThat(map->contains(ptr), IsTrue());
    AssertThat(map->get<Dog*>(ptr)->name(), Equals("Rover"));

    // String type
    map->clear();
    AssertThat(map->pointers()->size(), Equals(0));
    AssertThat(map->contains(ptr), IsFalse());
    map->insert(ptr, "hello");
    AssertThat(map->pointers()->size(), Equals(1));
    AssertThat(map->contains(ptr), IsTrue());
    AssertThat(map->get<const char*>(ptr), Equals("hello"));
}
