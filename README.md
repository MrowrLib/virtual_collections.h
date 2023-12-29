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

## What?

...

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
    add_packages("fmt") -- if using 'fmt'
```

### vcpkg

#### `CMakeLists.txt`

```cmake
add_executable(Example main.cpp)

# Find virtual_collections and link it to your target
find_package(virtual_collections CONFIG REQUIRED)
target_link_libraries(Example PRIVATE virtual_collections::virtual_collections)
```

#### `vcpkg.json`

```json
{
    "dependencies": ["mrowr-virtual-collections"]
}
```

And if you want to use `fmt`:

```json
{
    "dependencies": ["mrowr-virtual-collections", "fmt"]
}
```

#### `vcpkg-configuration.json`

```json
{
    "default-registry": {
        "kind": "git",
        "repository": "https://github.com/microsoft/vcpkg.git",
        "baseline": "95252eadd63118201b0d0df0b4360fa613f0de84"
    },
    "registries": [
        {
            "kind": "git",
            "repository": "https://github.com/MrowrLib/Packages.git",
            "baseline": "a10d9e3ed79e875558cfb1aa3cd012a71a102815",
            "packages": ["mrowr-virtual-collections"]
        }
    ]
}
```

> _Update the default-registry baseline to the latest commit from https://github.com/microsoft/vcpkg_  
> _Update the MrowrLib/Packages baseline to the latest commit from https://github.com/MrowrLib/Packages_

## Why?

...

## How?

...

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
