#define SPEC_GROUP VirtualTypedMap

#include <virtual_collections/map.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Example("restrict the type of keys in map") {
    VirtualMap untyped;

    auto typed = untyped.typed<const char*>();

    AssertThat(typed.contains("one"), Equals(false));
    AssertThat(typed.size(), Equals(0));
    typed.insert("one", 1);
    AssertThat(typed.contains("one"), Equals(true));
    AssertThat(typed.size(), Equals(1));
    AssertThat(typed.get<int>("one"), Equals(1));

    AssertThat(typed.contains("two"), Equals(false));
    typed.insert("two", 2);
    AssertThat(typed.contains("two"), Equals(true));
    AssertThat(typed.size(), Equals(2));
    AssertThat(typed.get<int>("one"), Equals(1));
    AssertThat(typed.get<int>("two"), Equals(2));

    typed.erase("one");

    AssertThat(typed.contains("one"), Equals(false));
    AssertThat(typed.size(), Equals(1));
}

Example("restrict the type of keys and values in map") {
    VirtualMap untyped;

    auto typed = untyped.typed<const char*, int>();

    AssertThat(typed.contains("one"), Equals(false));
    AssertThat(typed.size(), Equals(0));
    typed.insert("one", 1);
    AssertThat(typed.contains("one"), Equals(true));
    AssertThat(typed.size(), Equals(1));
    AssertThat(typed["one"], Equals(1));

    AssertThat(typed.contains("two"), Equals(false));
    typed.insert("two", 2);
    AssertThat(typed.contains("two"), Equals(true));
    AssertThat(typed.size(), Equals(2));
    AssertThat(typed["one"], Equals(1));
    AssertThat(typed["two"], Equals(2));

    typed.erase("one");

    AssertThat(typed.contains("one"), Equals(false));
    AssertThat(typed.size(), Equals(1));
}
