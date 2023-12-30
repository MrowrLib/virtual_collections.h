```
TODO

Add Const versions of every collection.

Lazy and const.

Const support const get() functions!

The current ones don't due to lazy initialization of underlying containers.
```

---

# `#include <virtual_collections.h>`

```cpp
#include <virtual_collections.h>

void Example() {
    // Pure virtual interfaces
    // that can be shared across DLL boundaries
    IVirtualArray* array = new VirtualArray();
    IVirtualMap*   map   = new VirtualMap();
    IVirtualSet*   set   = new Virtualinsert();

    // The collections provide most of the functionality you'd expect
    array->push("Hello");
    map->insert("Hello", "World");
    set->insert("Hello");
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
    - [`IVoidPointer` (`void*` with `delete` support)](#ivoidpointer-void-with-delete-support)
    - [`IFunctionPointer` (`virtual` function pointer)](#ifunctionpointer-virtual-function-pointer)
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
      - [`get()`](#get)
      - [`contains()`](#contains)
      - [`size()`](#size-1)
      - [`clear()`](#clear-1)
      - [`foreach()`](#foreach-1)
    - [Set](#set)
      - [`VirtualSet()` (_implementation_)](#virtualset-implementation)
        - [`VirtualConstSet()` and `VirtualLazySet()`](#virtualconstset-and-virtuallazyset)
      - [`insert()`](#insert-2)
      - [`contains()`](#contains-1)
      - [`size()`](#size-2)
      - [`clear()`](#clear-2)
      - [`foreach()`](#foreach-2)
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

tarat("Example")
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
            "baseline": "b44a121d79f6035161b3aeaa5354b56ce903ea19",
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

Collections support the following types:

- Boolean
- Integral types (`int`, `unsigned int`, ...) - _stored as `int`_
- Floating point types (`float`, `double`, ...) - _stored as `double`_
- C style strings (`const char*`) - _stored as `std::string`_
- Pointers - _stored as `void*`_

### `IVoidPointer` (`void*` with `delete` support)

Containers store most items wrapped in a `IVoidPointer` which is a `void*` with `delete` support.

> **`<void_pointer.h>`**`
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
array.erase(0);
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

> `VirtualSet` (`const` and _lazy_) use 5x internal `unordered_map` containers to store values (_of different types: bool, int, double, string, pointer_).
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
