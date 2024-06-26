# `#include <virtual_collections.h>`

```cpp
#include <virtual_collections.h>

void Example() {
    // Pure virtual interfaces
    // that can be shared across DLL boundaries
    IVirtualArray* array = new VirtualArray();
    IVirtualMap*   map   = new VirtualMap();
    IVirtualSet*   set   = new VirtualSet();

    // The collections provide most of the functionality you'd expect
    array->push("Hello");
    map->insert("Hello", "World");
    set->insert("Hello");

    // Optional type safety
    auto intArray = array->typed<int>();
    intArray->push(69);
}
```

- [`#include <virtual_collections.h>`](#include-virtual_collectionsh)
  - [What?](#what)
  - [Installation](#installation)
    - [xmake](#xmake)
      - [`xmake.lua`](#xmakelua)
    - [vcpkg](#vcpkg)
      - [`CMakeLists.txt`](#cmakeliststxt)
      - [`vcpkg.json`](#vcpkgjson)
      - [`vcpkg-configuration.json`](#vcpkg-configurationjson)
  - [Why?](#why)
  - [How?](#how)
  - [Supported Types](#supported-types)
    - [`bool`, `int`, `double`, `const char*`, `void*`](#bool-int-double-const-char-void)
    - [`IVoidPointer` (`void*` with `delete` support)](#ivoidpointer-void-with-delete-support)
    - [`IFunctionPointer` (`virtual` function pointer)](#ifunctionpointer-virtual-function-pointer)
  - [Bring your own containers](#bring-your-own-containers)
  - [Memory Management and Ownership](#memory-management-and-ownership)
    - [Configuring Value Ownership](#configuring-value-ownership)
      - [`IVirtualArray.push(value, destructable = true)`](#ivirtualarraypushvalue-destructable--true)
      - [`IVirtualMap.insert(key, value, destructable = true)`](#ivirtualmapinsertkey-value-destructable--true)
  - [Collections](#collections)
    - [Array](#array)
        - [`VirtualArray()` (_implementation_)](#virtualarray-implementation)
      - [`push()`](#push)
      - [`at()`](#at)
      - [`first()` / `last()`](#first--last)
      - [`size()`](#size)
      - [`clear()`](#clear)
      - [`insert()`](#insert)
      - [`erase()`](#erase)
      - [ranged `for` loop](#ranged-for-loop)
        - [templated `for` loop (`iterable<T>`)](#templated-for-loop-iterablet)
      - [`foreach()`](#foreach)
    - [Map](#map)
      - [`VirtualMap()` (_implementation_)](#virtualmap-implementation)
        - [`VirtualConstMap()` and `VirtualLazyMap()`](#virtualconstmap-and-virtuallazymap)
      - [`insert()`](#insert-1)
      - [`erase()`](#erase-1)
      - [`get()`](#get)
      - [`contains()`](#contains)
      - [`size()`](#size-1)
      - [`clear()`](#clear-1)
      - [`foreach()`](#foreach-1)
    - [Set](#set)
      - [`VirtualSet()` (_implementation_)](#virtualset-implementation)
        - [`VirtualConstSet()` and `VirtualLazySet()`](#virtualconstset-and-virtuallazyset)
      - [`insert()`](#insert-2)
      - [`erase()`](#erase-2)
      - [`contains()`](#contains-1)
      - [`size()`](#size-2)
      - [`clear()`](#clear-2)
      - [`foreach()`](#foreach-2)
  - [Type Safe Collections](#type-safe-collections)
    - [Typed Array](#typed-array)
    - [Typed Map](#typed-map)
    - [Typed Map (key only)](#typed-map-key-only)
    - [Typed Set](#typed-set)
  - [License](#license)

## What?

Pure `virtual` collection classes (`Map`, `Set`, `Array`) that can safely be used across DLL boundaries.

## Installation

### xmake

#### `xmake.lua`

```lua
add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")
add_requires("virtual_collections")

-- C++17 and above
set_languages("c++17")

target("Example")
    add_packages("virtual_collections")
```

### vcpkg

#### `CMakeLists.txt`

```cmake
add_executable(Example main.cpp)

# Find virtual_collections and link it to your tarat
find_package(virtual_collections CONFIG REQUIRED)
tarat_link_libraries(Example PRIVATE virtual_collections::virtual_collections)
```

#### `vcpkg.json`

```json
{
    "dependencies": ["mrowr-virtual-collections"]
}
```

#### `vcpkg-configuration.json`

```json
{
    "default-registry": {
        "kind": "git",
        "repository": "https://github.com/microsoft/vcpkg.git",
        "baseline": "83972272512ce4ede5fc3b2ba98f6468b179f192"
    },
    "registries": [
        {
            "kind": "git",
            "repository": "https://github.com/MrowrLib/Packages.git",
            "baseline": "db437bd66976eac282b57cb2068f32351a7373de",
            "packages": [
                "mrowr-virtual-collections",
                "mrowr-void-pointer",
                "mrowr-function-pointer",
                "mrowr-collections"
            ]
        }
    ]
}
```

> _Update the default-registry baseline to the latest commit from https://github.com/microsoft/vcpkg_  
> _Update the MrowrLib/Packages baseline to the latest commit from https://github.com/MrowrLib/Packages_

## Why?

I wanted container classes which could be safely used across DLL boundaries.

I kept creating my own collection classes for certain types, but what I really
wanted was generic collection classes which can store any type.

## How?

Pure abstract interfaces providing virtual functions are provided for each collection type.

If you only want to include the interfaces, you can `#include <virtual_collections/interfaces.h>`.

If you want to include the implementations, you can `#include <virtual_collections.h>`.

> **Including specific virtual collection interfaces**
> 
> - `IVirtualArray` (_abstract_) is available via `#include <virtual_collections/virtual_array.h>`
> - `IVirtualMap` (_abstract_) is available via `#include <virtual_collections/virtual_map.h>`
> - `IVirtualSet` (_abstract_) is available via `#include <virtual_collections/virtual_set.h>`

> **Including specific virtual collection implementations**
> 
> - `VirtualArray` (_implementation_) is available via `#include <virtual_collections/array.h>`
> - `VirtualMap` (_implementation_) is available via `#include <virtual_collections/map.h>`
> - `VirtualSet` (_implementation_) is available via `#include <virtual_collections/set.h>`

## Supported Types

The collections only support types which are natively safe to use across DLL boundaries.

> _No custom `dllexport` types are supported._

### `bool`, `int`, `double`, `const char*`, `void*`

Collections support the following types:

- Boolean
- Integral types (`int`, `unsigned int`, `uint8_t`, ...) - _stored as `int`_
- Floating point types (`float`, `double`, ...) - _stored as `double`_
- C style strings (`const char*`) - _stored as `std::string`_
- Pointers - _stored as `void*`_

### `IVoidPointer` (`void*` with `delete` support)

Array and Map containers store element values wrapped in a `IVoidPointer` which is a `void*` with `delete` support.

> **`<void_pointer.h>`**
>
> https://github.com/MrowrLib/void_pointer.h

You will likely not interact with `IVoidPointer` directly, but it is used internally by the collections.

The only thing you really need to know about an `IVoidPointer` is:

- If you have one and you want the value it points to, you can use `IVoidPointer::as<T>()` to get the value as a `T`.
- If the value you want is a pointer, you can use `IVoidPointer::as<T*>()` to get the value as a `T*`.

Here are some functions where you may interact with an `IVoidPointer`:

- `IVirtualArray.push_pointer(IPointer* pointer)` - _if you don't use a templated version of the `push()` function_
- `IVirtualArray.insert_pointer(unsigned int index, IPointer* pointer)` - _if you don't use a templated version of the `insert()` function_
- `for (auto* element : *array)` - _if you use a ranged `for` loop on the `IVirtualArray`, each element is an `IVoidPointer*`_

And every collection offers `foreach`, `foreach_value`, and `foreach_key_and_value` functions which take `std::function` callbacks and provide `IVoidPointer*` as arguments.

### `IFunctionPointer` (`virtual` function pointer)

The low-level `foreach*` functions take `IFunctionPointer*` callbacks as arguments.

> **`<function_pointer.h>`**`
>
> https://github.com/MrowrLib/function_pointer.h

Like `IVoidPointer`, you will likely not interact with `IFunctionPointer` directly, but it is used internally by the collections.

You can use the higher-level `foreach*` functions which take `std::function` callbacks (_which safely use `IFunctionPointer` internally for safe cross-DLL callbacks_).

## Bring your own containers

`<virtual_collections.h>` uses the `<collections.h>` library which allows for your to bring your own containers.

> **`<collections.h>`**
>
> https://github.com/MrowrLib/collections.h

All you have to do is install one of the following and the containers will be used instead of the `std::` ones:

- `unordered_dense` (_recommended_)
- `parallel-hashmap`
- `robin-hood-hashing`

See `<collections.h>` for more information.

## Memory Management and Ownership

Any pointers added as the following will be owned by the collection:

- Pointers added to `IVirtualArray`
- Pointers added to `IVirtualMap` as **values**
  
`VirtualSet` and `VirtualMap` do not take ownership of **key** pointers:

```cpp
auto pointerKey = new Dog();

VirtualArray array;
array.push(pointerKey); // array DOES own pointerKey

VirtualSet set;
set.insert(pointerKey); // set does NOT own pointerKey

VirtualMap map;
map.insert(pointerKey, "Dog"); // map does NOT own pointerKey
map.insert("Pointer as value", pointerKey); // map DOES own pointerKey
```

By default, the following will `delete` an owned pointer:

- Calling `clear()` on any collection
- Destroying an element via `erase()`

### Configuring Value Ownership

What if you want to store a pointer in a `IVirtualArray` or as the **value**
in a `IVirtualMap` but you don't want the collection to own it?

#### `IVirtualArray.push(value, destructable = true)`

Whenever you add a raw pointer to a `IVirtualArray`, you can specify whether or not the collection should own it.

```cpp
auto* pointer = new Dog();

VirtualArray array;

array.push(pointer); // array DOES own pointer
array.push(pointer, false); // array does NOT own pointer
```

#### `IVirtualMap.insert(key, value, destructable = true)`

Whenever you add a raw pointer to a `IVirtualMap` as the **value**, you can specify whether or not the collection should own it.

```cpp
auto* pointer = new Dog();

VirtualMap map;

map.insert("Dog", pointer); // map DOES own pointer
map.insert("Dog", pointer, false); // map does NOT own pointer
```

## Collections

### Array

##### `VirtualArray()` (_implementation_)

```cpp
#include <virtual_collections.h>

VirtualArray array;
```

#### `push()`

```cpp
array.push(true); // boolean
array.push(69);  // int
array.push(3.14); // double
array.push("Hello World"); // const char*
array.push(new Dog()); // pointer
```

#### `at()`

```cpp
bool        boolean       = array.at<bool>(0);
int         integer       = array.at<int>(1);
double      floatingPoint = array.at<double>(2);
const char* string        = array.at<const char*>(3);
Dog*        pointer       = array.at<Dog*>(4);
```

#### `first()` / `last()`

```cpp
bool        boolean       = array.first<bool>();
int         integer       = array.first<int>();
double      floatingPoint = array.first<double>();
const char* string        = array.first<const char*>();
Dog*        pointer       = array.first<Dog*>();
```

#### `size()`

```cpp
unsigned int size = array.size();
```

#### `clear()`

```cpp
array.clear();
```

#### `insert()`

```cpp
array.insert(0, true); // boolean
array.insert(1, 69);  // int
array.insert(2, 3.14); // double
array.insert(3, "Hello World"); // const char*
array.insert(4, new Dog()); // pointer
```

#### `erase()`

```cpp
array.erase(0); // erase element at index 0

array.erase(0, 2); // erase 2 elements starting at index 0
```

#### ranged `for` loop

Using a `for` loop directly on the `IVirtualArray` will loop over items as `IVoidPointer` (_which is how they are stored_).

```cpp
for (auto* item : *array) {
    bool       boolean       = item->as<bool>();
    int        integer       = item->as<int>();
    double     floatingPoint = item->as<double>();
    const char string        = item->as<const char*>();
    Dog*       pointer       = item->as<Dog*>();
}
```

##### templated `for` loop (`iterable<T>`)

If you want to loop over items as their original type, you can use `iterable<T>`.

```cpp
for (auto number : array.iterable<int>()) {
    // Here, this int value is a copy of the original value
    // Under the hood .iterable<int> becomes IVoidPointer.as<int>
}

for (auto* dog : array.iterable<Dog*>()) {
    // Here, we get a pointer to the original value
    // Under the hood .iterable<Dog*> becomes IVoidPointer.as<Dog*>
}
```

#### `foreach()`

Various `foreach()` functions are provided which take a `std::function` callback:

Get the index and value (_as `IVoidPointer*`_):
- `foreach(std::function<void(unsigned int, IVoidPointer*)> callback)`

Get the value (_as `IVoidPointer*`_):
- `foreach_value(std::function<void(IVoidPointer*)> callback)`

Get the index and value (_as specified type_):
- `foreach(std::function<void(unsigned int, T)> callback)`

Get the value (_as specified type_):
- `foreach_value(std::function<void(T)> callback)`

```cpp
array.foreach([](unsigned int index, IVoidPointer* item) {
    bool       boolean       = item->as<bool>();
    int        integer       = item->as<int>();
    double     floatingPoint = item->as<double>();
    const char string        = item->as<const char*>();
    Dog*       pointer       = item->as<Dog*>();
});

array.foreach_value([](IVoidPointer* item) {
    bool       boolean       = item->as<bool>();
    int        integer       = item->as<int>();
    double     floatingPoint = item->as<double>();
    const char string        = item->as<const char*>();
    Dog*       pointer       = item->as<Dog*>();
});

array.foreach<int>([](unsigned int index, int item) {
    // ...
});

array.foreach<int>([](int item) {
    // ...
});
```

### Map

> _Note: at this time, the map does not support a range-based `for` loop iterator_
>
> _But you can use the available `foreach` functions instead!_

#### `VirtualMap()` (_implementation_)

```cpp
#include <virtual_collections.h>

VirtualMap map;
```

##### `VirtualConstMap()` and `VirtualLazyMap()`

By default, `VirtualMap()` is an alias for `VirtualConstMap()`.

`VirtualConstMap` provides `const` functions for lookup:

- `get()`
- `contains()`

It provides this at the cost of pre-allocating its underlying containers.

> `VirtualMap` (`const` and _lazy_) use 5x internal `unordered_map` containers to store values (_of different types: bool, int, double, string, pointer_).
>
> The default `VirtualMap` (`VirtualConstMap`) pre-initializes these containers.

`VirtualLazyMap` does NOT pre-allocate its underlying containers.

This comes at the cost of NOT supporting `const` lookups:

- `get()` ~ _only the non-`const` overload works, the `const` will return a `nullptr`_
- `contains()` ~ _only the non-`const` overload works, the `const` will return a `nullptr`_

#### `insert()`

```cpp
map.insert(true, "True"); // boolean
map.insert(69, "Sixty Nine");  // int
map.insert(3.14, "Pi"); // double
map.insert("Hello", "World"); // const char*
map.insert(new Dog(), "Dog"); // pointer
```

#### `erase()`

```cpp
map.erase(true); // boolean
map.erase(69);  // int
map.erase(3.14); // double
map.erase("Hello"); // const char*
map.erase(new Dog()); // pointer
```

#### `get()`

```cpp
bool       boolean       = map.get<bool>("True");
int        integer       = map.get<int>("Sixty Nine");
double     floatingPoint = map.get<double>("Pi");
const char string        = map.get<const char*>("World");
Dog*       pointer       = map.get<Dog*>("Dog");
```

#### `contains()`

```cpp
bool contains = map.contains("True");
bool contains = map.contains<bool>("True");
bool contains = map.contains<int>("Sixty Nine");
bool contains = map.contains<double>("Pi");
bool contains = map.contains<const char*>("World");
```

#### `size()`

```cpp
unsigned int size = map.size();
```

#### `clear()`

```cpp
map.clear();
```

#### `foreach()`

Various `foreach()` functions are provided which take a `std::function` callback:

Get the key and value (_both as `IVoidPointer*`_):
- `foreach(std::function<void(IVoidPointer*, IVoidPointer*)> callback)`

Get the key (_as specified type_) and value (_as `IVoidPointer*`_):
- `foreach<TKeyType>(std::function<void(TKeyType, IVoidPointer*)> callback)`

Get the key (_as specified type_) and value (_as specified type_):
- `foreach<TKeyType, TValueType>(std::function<void(TKeyType, TValueType)> callback)`

```cpp
map.foreach([](IVoidPointer* key, IVoidPointer* value) {
    // Keys as IVoidPointer*
    bool       boolean       = key->as<bool>();
    int        integer       = key->as<int>();
    double     floatingPoint = key->as<double>();
    const char string        = key->as<const char*>();
    Dog*       pointer       = key->as<Dog*>();
    // Values as IVoidPointer*
    bool       boolean       = value->as<bool>();
    int        integer       = value->as<int>();
    double     floatingPoint = value->as<double>();
    const char string        = value->as<const char*>();
    Dog*       pointer       = value->as<Dog*>();
});

map.foreach<bool>([](bool key, IVoidPointer* value) {
    // Keys as bool
    // Values as IVoidPointer*
});

map.foreach<bool, int>([](bool key, int value) {
    // Keys as bool
    // Values as int
});
```

### Set

> _Note: at this time, the set does not support a range-based `for` loop iterator_
>
> _But you can use the available `foreach` functions instead!_

#### `VirtualSet()` (_implementation_)

```cpp
#include <virtual_collections.h>

VirtualSet set;
```

##### `VirtualConstSet()` and `VirtualLazySet()`

By default, `VirtualSet()` is an alias for `VirtualConstSet()`.

`VirtualConstSet` provides `const` functions for lookup:

- `contains()`

It provides this at the cost of pre-allocating its underlying containers.

> `VirtualSet` (`const` and _lazy_) use 5x internal `unordered_set` containers to store values (_of different types: bool, int, double, string, pointer_).
>
> The default `VirtualSet` (`VirtualConstSet`) pre-initializes these containers.

`VirtualLazySet` does NOT pre-allocate its underlying containers.

This comes at the cost of NOT supporting `const` lookups:

- `contains()` ~ _only the non-`const` overload works, the `const` will return a `nullptr`_

#### `insert()`

```cpp
set.insert(true); // boolean
set.insert(69);  // int
set.insert(3.14); // double
set.insert("Hello World"); // const char*
set.insert(new Dog()); // pointer
```

#### `erase()`

```cpp
set.erase(true); // boolean
set.erase(69);  // int
set.erase(3.14); // double
set.erase("Hello World"); // const char*
set.erase(new Dog()); // pointer
```

#### `contains()`

```cpp
bool contains = set.contains(true);
bool contains = set.contains(69);
bool contains = set.contains(3.14);
bool contains = set.contains("Hello World");
```

#### `size()`

```cpp
unsigned int size = set.size();
```

#### `clear()`

```cpp
set.clear();
```

#### `foreach()`

Various `foreach()` functions are provided which take a `std::function` callback:

Get the value (_as `IVoidPointer*`_):
- `foreach(std::function<void(IVoidPointer*)> callback)`

Get the value (_as specified type_):
- `foreach<TValueType>(std::function<void(TValueType)> callback)`

```cpp
set.foreach([](IVoidPointer* value) {
    // Values as IVoidPointer*
    bool       boolean       = value->as<bool>();
    int        integer       = value->as<int>();
    double     floatingPoint = value->as<double>();
    const char string        = value->as<const char*>();
    Dog*       pointer       = value->as<Dog*>();
});

set.foreach<int>([](int value) {
    // Values as int
});
```

## Type Safe Collections

None of the collections are type safe by default.

You can put anything you want into them and attempt to read anything back out.

If you want type safety, you can use the templated versions of the collections:

- `TypedArray<T>`
- `TypedMap<TKey>`
- `TypedMap<TKey, TValue>`
- `TypedSet<T>`

These classes have the same interface as the non-templated collections, but they are type safe.

The compiler will not allow storage of anything other than the specified type.

There is no abstract base class for the typed collections and you should not store them.
Instead, store the underlying collection and use `.typed<T>()` to get a typed wrapper as needed.

> Note: these are nothing more than wrappers around the non-templated collections.
>
> These require an instance of the non-templated collection to be passed to their constructor.
>
> If you destroy the typed collection, the non-templated collection will NOT be destroyed.
>
> You can configure the typed collection to delete the underlying collection by passing `true` to the `[collection].typed<T>(bool destructable)` function.

### Typed Array

```cpp
VirtualArray untyped;

// Then, when you want compiler type safety...
auto array = untyped->typed<int>();

// Now, you can use the typed array
array->push(69);

auto integer = array->at(0); // You do not need to use at<T> to get a typed value
auto integer = array[0];     // You can also use the [] operator to get a typed value

// You can also use the typed array in a ranged for loop
for (auto number : array) {
    // ...
}

// To loop with the index, you can use foreach
array->foreach([](unsigned int index, int number) {
    // ...
});

// foreach also supports only the element
array->foreach([](int number) {
    // ...
});
```

### Typed Map

> _Note: at this time, the typed map does not support a range-based `for` loop iterator_

```cpp
VirtualMap untyped;

// Then, when you want compiler type safety...
auto map = untyped->typed<int, double>();

// Now, you can use the typed map
map->insert(69, 3.14);

double value = map->get(69); // You do not need to use get<T> to get a typed value

// Use foreach to loop over key and value
map->foreach([](int key, double value) {
    // ...
});
```

### Typed Map (key only)

> _Note: at this time, the typed map does not support a range-based `for` loop iterator_

Perhaps less useful, you can _also_ use the typed map with only a typed key.

```cpp
VirtualMap untyped;

// Then, when you want compiler type safety...
auto map = untyped->typed<int>(); // key only

// Now, you can use the typed map
map->insert(69, "Sixty Nine");

auto value = map->get<const char*>(69); // You still need to use get<T> to get a typed value

// Use foreach to loop over key and value
// You still need to provide the T for the value (but not the key)
map->foreach<const char*>([](int key, const char* value) {
    // ...
});
```

### Typed Set

> _Note: at this time, the typed set does not support a range-based `for` loop iterator_

```cpp
VirtualSet untyped;

// Then, when you want compiler type safety...
auto set = untyped->typed<int>();

// Now, you can use the typed set
set->insert(69);

// Use foreach to loop over value
set->foreach([](int value) {
    // ...
});
```

## License

Use however, no attribution required.

```
BSD Zero Clause License (SPDX: 0BSD)

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
```
