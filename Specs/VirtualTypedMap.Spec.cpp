#define SPEC_GROUP VirtualTypedMap

#include <virtual_collections/map.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Example("restrict the type of keys in map") {
    VirtualMap untyped;

    auto map = untyped.typed<const char*>();

    AssertThat(map.contains("one"), Equals(false));
    AssertThat(map.size(), Equals(0));
    map.insert("one", 1);
    AssertThat(map.contains("one"), Equals(true));
    AssertThat(map.size(), Equals(1));
    AssertThat(map.get<int>("one"), Equals(1));

    AssertThat(map.contains("two"), Equals(false));
    map.insert("two", 2);
    AssertThat(map.contains("two"), Equals(true));
    AssertThat(map.size(), Equals(2));
    AssertThat(map.get<int>("one"), Equals(1));
    AssertThat(map.get<int>("two"), Equals(2));

    map.erase("one");

    AssertThat(map.contains("one"), Equals(false));
    AssertThat(map.size(), Equals(1));
}

Example("restrict the type of keys and values in map") {
    VirtualMap untyped;

    auto map = untyped.typed<const char*, int>();

    AssertThat(map.contains("one"), Equals(false));
    AssertThat(map.size(), Equals(0));
    map.insert("one", 1);
    AssertThat(map.contains("one"), Equals(true));
    AssertThat(map.size(), Equals(1));
    AssertThat(map["one"], Equals(1));

    AssertThat(map.contains("two"), Equals(false));
    map.insert("two", 2);
    AssertThat(map.contains("two"), Equals(true));
    AssertThat(map.size(), Equals(2));
    AssertThat(map["one"], Equals(1));
    AssertThat(map["two"], Equals(2));

    map.erase("one");

    AssertThat(map.contains("one"), Equals(false));
    AssertThat(map.size(), Equals(1));
}

Example("foreach over key and values") {
    std::vector<std::string> keys;
    std::vector<int>         values;

    VirtualMap untyped;

    auto map = untyped.typed<const char*, int>();

    map.insert("one", 1);
    map.insert("two", 2);
    map.insert("three", 3);

    map.foreach([&keys, &values](const char* key, int value) {
        keys.push_back(key);
        values.push_back(value);
    });

    AssertThat(keys.size(), Equals(3));
    AssertThat(keys, Has().Exactly(1).EqualTo("one"));
    AssertThat(keys, Has().Exactly(1).EqualTo("two"));
    AssertThat(keys, Has().Exactly(1).EqualTo("three"));

    AssertThat(values.size(), Equals(3));
    AssertThat(values, Has().Exactly(1).EqualTo(1));
    AssertThat(values, Has().Exactly(1).EqualTo(2));
    AssertThat(values, Has().Exactly(1).EqualTo(3));
}
