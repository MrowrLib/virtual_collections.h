#define SPEC_GROUP VirtualMap_Default

#include <virtual_collections/map.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Setup { current_test->var<IVirtualMap>("map", new VirtualMap()); }

UseTemplate("Map Examples");
