#define SPEC_GROUP VirtualMap

#include <virtual_collections/map.h>

#include "SpecHelper.h"  // IWYU pragma: keep

struct Dog {
    std::string _name;
    Dog(std::string name) : _name(name) { _Log_("Dog {} is created", _name); }
    ~Dog() { _Log_("Dog {} is destroyed", _name); }
    std::string name() { return _name; }
};

Example("boolean key map") {
    auto map = std::unique_ptr<IVirtualMap>(new VirtualMap());

    // Value Type
    AssertThat(map->bools()->size(), Equals(0));
    AssertThat(map->contains(true), IsFalse());
    map->insert(true, 123);
    AssertThat(map->bools()->size(), Equals(1));
    AssertThat(map->contains(true), IsTrue());
    AssertThat(map->get<int>(true), Equals(123));

    // Pointer Type
    AssertThat(map->bools()->size(), Equals(1));
    AssertThat(map->contains(false), IsFalse());
    map->insert(false, new Dog("Rover"));
    AssertThat(map->bools()->size(), Equals(2));
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
    auto map = std::unique_ptr<IVirtualMap>(new VirtualMap());

    // Value Type
    AssertThat(map->ints()->size(), Equals(0));
    AssertThat(map->contains(123), IsFalse());
    map->insert(123, 456);
    AssertThat(map->ints()->size(), Equals(1));
    AssertThat(map->contains(123), IsTrue());
    AssertThat(map->get<int>(123), Equals(456));

    // String type

    // Pointer Type
    AssertThat(map->ints()->size(), Equals(1));
    AssertThat(map->contains(456), IsFalse());
    map->insert(456, new Dog("Rover"));
    AssertThat(map->ints()->size(), Equals(2));
    AssertThat(map->contains(456), IsTrue());
    AssertThat(map->get<Dog*>(456)->name(), Equals("Rover"));
}

Example("floating point key map") {
    auto map = std::unique_ptr<IVirtualMap>(new VirtualMap());

    // Value Type
    AssertThat(map->floating_points()->size(), Equals(0));
    AssertThat(map->contains(123.456), IsFalse());
    map->insert(123.456, 456.789);
    AssertThat(map->floating_points()->size(), Equals(1));
    AssertThat(map->contains(123.456), IsTrue());
    AssertThat(map->get<double>(123.456), Equals(456.789));

    // String Type

    // Pointer Type
    AssertThat(map->floating_points()->size(), Equals(1));
    AssertThat(map->contains(456.789), IsFalse());
    map->insert(456.789, new Dog("Rover"));
    AssertThat(map->floating_points()->size(), Equals(2));
    AssertThat(map->contains(456.789), IsTrue());
    AssertThat(map->get<Dog*>(456.789)->name(), Equals("Rover"));
}

Example("string key map") {
    auto map = std::unique_ptr<IVirtualMap>(new VirtualMap());

    // Value Type
    // AssertThat(map->strings()->size(), Equals(0));
    // AssertThat(map->contains("hello"), IsFalse());
    // map->insert("hello", "world");
    // AssertThat(map->strings()->size(), Equals(1));
    // AssertThat(map->contains("hello"), IsTrue());
    // AssertThat(map->get<const char*>("hello"), Equals("world"));
}

// Example("pointer key map") {
//     auto map = std::unique_ptr<IVirtualMap>(new VirtualMap());

//     auto dog = std::make_unique<Dog>("Rover");

//     // auto value = map->get<Dog*, int>(dog.get());
//     // _Log_("The value is: {}", value);

//     // AssertThat(value, Equals(0));  // default value

//     // AssertThat(map->get<Dog*, int>(dog.get()), Equals(0));  // default value

//     // // Value type
//     // AssertThat(map->contains(dog.get()), IsFalse());
//     // map->insert(dog.get(), 456);
//     // AssertThat(map->contains(dog.get()), IsTrue());

//     // auto value = map->get<int>(dog.get());
//     // _Log_("The value is: {}", value);

//     // // Pointer type
//     // map->insert(dog.get(), new Dog("Rover"));
//     // auto dog2 = map->get<Dog*>(dog.get());
//     // _Log_("The dog is: {}", dog2->name());
// }
