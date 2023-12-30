#define SPEC_GROUP VirtualTypedSet

#include <virtual_collections/set.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Example("restrict the type of values in set") {
    VirtualSet untyped;

    auto set = untyped.typed<const char*>();

    AssertThat(set.contains("one"), Equals(false));
    AssertThat(set.size(), Equals(0));
    set.insert("one");
    AssertThat(set.contains("one"), Equals(true));
    AssertThat(set.size(), Equals(1));

    AssertThat(set.contains("two"), Equals(false));
    set.insert("two");
    AssertThat(set.contains("two"), Equals(true));
    AssertThat(set.size(), Equals(2));

    set.erase("one");

    AssertThat(set.contains("one"), Equals(false));
    AssertThat(set.size(), Equals(1));
}

Example("foreach over set elements") {
    std::vector<std::string> values;

    VirtualSet untyped;

    auto set = untyped.typed<const char*>();

    set.insert("one");
    set.insert("two");
    set.insert("three");

    set.foreach([&values](const char* value) { values.push_back(value); });

    AssertThat(values.size(), Equals(3));
    AssertThat(values[0], Equals("one"));
    AssertThat(values[1], Equals("two"));
    AssertThat(values[2], Equals("three"));
}
