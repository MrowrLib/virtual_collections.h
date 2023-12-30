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
  - [Collections](#collections)
    - [Array](#array)
        - [`VirtualArray` (_implementation_)](#virtualarray-implementation)
      - [`push()`](#push)
      - [`at()`](#at)
      - [`first()` / `last()`](#first--last)
      - [`size()`](#size)
      - [`clear()`](#clear)
      - [`insert()`](#insert)
      - [`erase()`](#erase)
    - [Map](#map)
    - [Set](#set)
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
            "baseline": "e92d44a318763b1e49b51f23134a31ad624d2d6d",
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

## Collections

### Array

##### `VirtualArray` (_implementation_)

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

### Map

### Set
    
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
