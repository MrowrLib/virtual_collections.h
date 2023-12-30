#define SPEC_GROUP VirtualSet_Const

#include <virtual_collections/const_set.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Setup { current_test->var<IVirtualSet>("set", new VirtualConstSet()); }

UseTemplate("Set Examples");
