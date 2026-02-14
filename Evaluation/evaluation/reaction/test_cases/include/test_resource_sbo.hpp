#pragma once

#include <reaction/core/resource.h>
#include <array>

namespace test_reaction {

struct ResourceSBOState {
    bool smallTypeUsesSBO;
    bool largeTypeUsesSBO;
};

/**
 * Function: Inspect whether Resource leverages SBO depending on value size
 *
 * @return ResourceSBOState SBO usage flags for small vs large types
 */
ResourceSBOState test_resource_sbo() {
    using SmallResource = reaction::Resource<int>;
    using LargeArray = std::array<int, 256>;
    using LargeResource = reaction::Resource<LargeArray>;

    SmallResource smallRes(42);
    LargeResource largeRes(LargeArray{});

    return ResourceSBOState{
        .smallTypeUsesSBO = smallRes.isUsingSBO(),
        .largeTypeUsesSBO = largeRes.isUsingSBO(),
    };
}

}  // namespace test_reaction


