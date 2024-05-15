#define SPEC_GROUP VirtualTypedArray

#include <virtual_collections/array.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Example("restrict the type of elements in a array") {
    VirtualArray untyped;

    auto array = untyped.typed<int>();

    AssertThat(array.size(), Equals(0));
    array.push(1);
    AssertThat(array.size(), Equals(1));

    AssertThat(array[0], Equals(1));

    array.push(2);
    AssertThat(array.size(), Equals(2));

    AssertThat(array[0], Equals(1));
    AssertThat(array[1], Equals(2));

    array.insert(1, 3);
    AssertThat(array.size(), Equals(3));

    AssertThat(array[0], Equals(1));
    AssertThat(array[1], Equals(3));
    AssertThat(array[2], Equals(2));

    array.erase(1);

    AssertThat(array.size(), Equals(2));
    AssertThat(array[0], Equals(1));
    AssertThat(array[1], Equals(2));
}

Example("foreach over elements") {
    std::vector<double> values;

    VirtualArray untyped;

    auto array = untyped.typed<double>();

    array.push(1.0);
    array.push(2.0);
    array.push(3.0);

    array.foreach([&values](double value) { values.push_back(value); });

    AssertThat(values.size(), Equals(3));
    AssertThat(values[0], Equals(1.0));
    AssertThat(values[1], Equals(2.0));
    AssertThat(values[2], Equals(3.0));
}

Example("foreach over elements with index") {
    std::vector<int>    indexes;
    std::vector<double> values;

    VirtualArray untyped;

    auto array = untyped.typed<double>();

    array.push(1.0);
    array.push(2.0);
    array.push(3.0);

    array.foreach([&indexes, &values](unsigned int index, double value) {
        indexes.push_back(index);
        values.push_back(value);
    });

    AssertThat(indexes.size(), Equals(3));
    AssertThat(indexes[0], Equals(0));
    AssertThat(indexes[1], Equals(1));
    AssertThat(indexes[2], Equals(2));

    AssertThat(values.size(), Equals(3));
    AssertThat(values[0], Equals(1.0));
    AssertThat(values[1], Equals(2.0));
    AssertThat(values[2], Equals(3.0));
}

Example("range based for loop") {
    std::vector<double> values;

    VirtualArray untyped;

    auto array = untyped.typed<double>();

    array.push(1.0);
    array.push(2.0);
    array.push(3.0);

    for (auto value : array) values.push_back(value);

    AssertThat(values.size(), Equals(3));
    AssertThat(values[0], Equals(1.0));
    AssertThat(values[1], Equals(2.0));
    AssertThat(values[2], Equals(3.0));
}

Example("range based for loop with pointer values") {
    std::vector<Dog*> values;

    VirtualArray untyped;

    auto array = untyped.typed<Dog*>();

    array.push(new Dog("Fido"));
    array.push(new Dog("Rex"));
    array.push(new Dog("Lassie"));

    for (auto* value : array) values.push_back(value);

    AssertThat(values.size(), Equals(3));
    AssertThat(values[0]->name(), Equals("Fido"));
    AssertThat(values[1]->name(), Equals("Rex"));
    AssertThat(values[2]->name(), Equals("Lassie"));
}

Example("strings") {
    VirtualArray untyped;

    auto array = untyped.typed<const char*>();

    array.push("one");
    array.push("two");
    array.push("three");

    AssertThat(array.size(), Equals(3));
    AssertThat(array[0], Equals("one"));
    AssertThat(array[1], Equals("two"));
    AssertThat(array[2], Equals("three"));
}
