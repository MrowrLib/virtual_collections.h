add_requires(
    "specs", "fmt",
    "specs_snowhouse", "vcpkg::snowhouse",
    "specs_libassert", "libassert_latest",
    "_Log_", "spdlog"
    -- "unordered_dense",
    -- "parallel-hashmap",
    -- "robin-hood-hashing"
)

target("Specs")
    set_kind("binary")
    add_files("Templates/*.cpp", "*.cpp")
    add_includedirs(".")
    add_deps("virtual_collections")
    add_packages(
        "specs", "fmt",
        "specs_snowhouse", "vcpkg::snowhouse",
        "specs_libassert", "libassert_latest",
        "_Log_", "spdlog"
    )
