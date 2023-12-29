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

    // Value type
    map->insert(true, 123);
    auto value = map->get<int>(true);
    _Log_("The value is: {}", value);

    // Pointer type
    map->insert(false, new Dog("Rover"));
    auto dog = map->get<Dog*>(false);
    _Log_("The dog is: {}", dog->name());
}

Example("integer key map") {
    auto map = std::unique_ptr<IVirtualMap>(new VirtualMap());

    // Value type
    map->insert(123, 456);
    auto value = map->get<int>(123);
    _Log_("The value is: {}", value);

    // Pointer type
    map->insert(456, new Dog("Rover"));
    auto dog = map->get<Dog*>(456);
    _Log_("The dog is: {}", dog->name());
}

Example("floating point key map") {
    auto map = std::unique_ptr<IVirtualMap>(new VirtualMap());

    // Value type
    map->insert(123.456, 456.789);
    auto value = map->get<double>(123.456);
    _Log_("The value is: {}", value);

    // Pointer type
    map->insert(456.789, new Dog("Rover"));
    auto dog = map->get<Dog*>(456.789);
    _Log_("The dog is: {}", dog->name());
}

Example("string key map") {
    auto map = std::unique_ptr<IVirtualMap>(new VirtualMap());

    // Value type
    map->insert("123", "456");
    auto value = map->get<const char*>("123");
    _Log_("xxx The value is: {}", value);

    map->insert("456", 456);
    auto value2 = map->get<int>("456");
    _Log_("The value is: {}", value2);

    // Pointer type
    map->insert("456", new Dog("Rover"));
    auto dog = map->get<Dog*>("456");
    _Log_("The dog is: {}", dog->name());
}
