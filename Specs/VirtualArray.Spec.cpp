#define SPEC_GROUP VirtualArray

#include <virtual_collections/array.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Setup { current_test->var<IVirtualArray>("array", new VirtualArray()); }

UseTemplate("Array Examples");
