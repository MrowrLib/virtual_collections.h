#define SPEC_GROUP VirtualMap_Const

#include <virtual_collections/const_map.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Setup { current_test->var<IVirtualMap>("map", new VirtualConstMap()); }

UseTemplate("Map Examples");
