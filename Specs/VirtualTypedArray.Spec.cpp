#define SPEC_GROUP VirtualTypedArray

#include <virtual_collections/array.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Example("restrict the type of elements in a array") {
    VirtualArray untyped;

    auto typed = untyped.typed<int>();

    AssertThat(typed.size(), Equals(0));
    typed.push(1);
    AssertThat(typed.size(), Equals(1));

    AssertThat(typed[0], Equals(1));

    typed.push(2);
    AssertThat(typed.size(), Equals(2));

    AssertThat(typed[0], Equals(1));
    AssertThat(typed[1], Equals(2));

    typed.insert(1, 3);
    AssertThat(typed.size(), Equals(3));

    AssertThat(typed[0], Equals(1));
    AssertThat(typed[1], Equals(3));
    AssertThat(typed[2], Equals(2));

    typed.erase(1);

    AssertThat(typed.size(), Equals(2));
    AssertThat(typed[0], Equals(1));
    AssertThat(typed[1], Equals(2));
}
