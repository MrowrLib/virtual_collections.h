#define SPEC_GROUP VirtualSet_Lazy

#include <virtual_collections/lazy_set.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Setup { current_test->var<IVirtualSet>("set", new VirtualLazySet()); }

UseTemplate("Set Examples");
