#define SPEC_GROUP VirtualSet

#include <virtual_collections/set.h>

#include <memory>

#include "SpecHelper.h"  // IWYU pragma: keep

struct Dog {
    std::string _name;
    Dog(std::string name) : _name(name) { _Log_("Dog {} is created", _name); }
    ~Dog() { _Log_("Dog {} is destroyed", _name); }
    std::string name() { return _name; }
};

Example("usage example") {
    auto set = std::unique_ptr<IVirtualSet>(new VirtualSet());

    // bool

    AssertThat(set->contains(true), IsFalse());
    AssertThat(set->contains(false), IsFalse());
    AssertThat(set->bools()->size(), Equals(0));

    set->insert(true);

    AssertThat(set->bools()->size(), Equals(1));
    AssertThat(set->contains(true), IsTrue());
    AssertThat(set->contains(false), IsFalse());

    // int

    AssertThat(set->contains(123), IsFalse());
    AssertThat(set->ints()->size(), Equals(0));
    set->insert(123);
    AssertThat(set->ints()->size(), Equals(1));
    AssertThat(set->contains(123), IsTrue());

    auto setaddress = reinterpret_cast<std::uintptr_t>(set.get());
    AssertThat(set->contains(setaddress), IsFalse());
    AssertThat(set->ints()->size(), Equals(1));
    set->insert(setaddress);
    AssertThat(set->ints()->size(), Equals(2));
    AssertThat(set->contains(setaddress), IsTrue());

    // float

    AssertThat(set->contains(123.456), IsFalse());
    AssertThat(set->floating_points()->size(), Equals(0));
    set->insert(123.456);
    AssertThat(set->floating_points()->size(), Equals(1));
    AssertThat(set->contains(123.456), IsTrue());

    // string

    AssertThat(set->contains("hello"), IsFalse());
    AssertThat(set->strings()->size(), Equals(0));
    set->insert("hello");
    AssertThat(set->strings()->size(), Equals(1));
    AssertThat(set->contains("hello"), IsTrue());

    // pointers

    auto dog = std::make_unique<Dog>("Fido");
    AssertThat(set->contains(dog.get()), IsFalse());
    AssertThat(set->pointers()->size(), Equals(0));
    set->insert(dog.get());
    AssertThat(set->pointers()->size(), Equals(1));
    AssertThat(set->contains(dog.get()), IsTrue());
}
