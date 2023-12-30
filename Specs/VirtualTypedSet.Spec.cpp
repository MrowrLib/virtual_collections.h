#define SPEC_GROUP VirtualTypedSet

#include <virtual_collections/set.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Example("restrict the type of values in set") {
    VirtualSet untyped;

    auto typed = untyped.typed<const char*>();

    AssertThat(typed.contains("one"), Equals(false));
    AssertThat(typed.size(), Equals(0));
    typed.insert("one");
    AssertThat(typed.contains("one"), Equals(true));
    AssertThat(typed.size(), Equals(1));

    AssertThat(typed.contains("two"), Equals(false));
    typed.insert("two");
    AssertThat(typed.contains("two"), Equals(true));
    AssertThat(typed.size(), Equals(2));

    typed.erase("one");

    AssertThat(typed.contains("one"), Equals(false));
    AssertThat(typed.size(), Equals(1));
}
