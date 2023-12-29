#pragma once

#include <Specs.h>
#include <Specs/LibAssert.h>
#include <Specs/Snowhouse.h>

#include <memory>  // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

struct Dog {
    std::string _name;
    Dog(std::string name) : _name(name) { _Log_("Dog {} is created", _name); }
    ~Dog() { _Log_("Dog {} is destroyed", _name); }
    std::string name() { return _name; }
};
