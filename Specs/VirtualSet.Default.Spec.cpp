#define SPEC_GROUP VirtualSet_Default

#include <virtual_collections/set.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Setup { current_test->var<IVirtualSet>("set", new VirtualSet()); }

UseTemplate("Set Examples");
