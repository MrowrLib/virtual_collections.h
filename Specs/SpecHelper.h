#pragma once

#include <Specs.h>
#include <Specs/LibAssert.h>
#include <Specs/Snowhouse.h>

#include <memory>  // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

class Dog {
    inline static unsigned int _totalDogCount = 0;
    std::string                _name;

public:
    Dog(std::string name) : _name(name) { _totalDogCount++; }
    ~Dog() { _totalDogCount--; }
    std::string         name() { return _name; }
    static unsigned int totalDogCount() { return _totalDogCount; }
    static void         resetTotalDogCount() { _totalDogCount = 0; }
};

Setup { Dog::resetTotalDogCount(); };
