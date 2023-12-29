add_requires(
    "specs", "fmt",
    "specs_snowhouse", "vcpkg::snowhouse",
    "specs_libassert", "libassert_latest",
    "_Log_", "spdlog"
)

target("Specs")
    set_kind("binary")
    add_files("*.cpp")
    add_deps("virtual_collections")
    add_packages(
        "specs", "fmt",
        "specs_snowhouse", "vcpkg::snowhouse",
        "specs_libassert", "libassert_latest",
        "_Log_", "spdlog"
    )
