#define SPEC_GROUP VirtualMap_Lazy

#include <virtual_collections/lazy_map.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Setup { current_test->var<IVirtualMap>("map", new VirtualLazyMap()); }

UseTemplate("Map Examples");
