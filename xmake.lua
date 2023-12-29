add_rules("mode.debug", "mode.releasedbg", "mode.release")

set_languages("c++20")

add_repositories("MrowrLib https://github.com/MrowrLib/Packages")

add_requires(
    "collections", "void_pointer", "function_pointer"
)

target("virtual_collections")
    set_kind("headeronly")
    add_includedirs("include", { public = true })
    add_packages("collections", "void_pointer", "function_pointer", { public = true })

includes("Specs/xmake.lua")
