

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "reaction/memory/sbo_resource.h"
#include "reaction/memory/stack_monitor.h"
#include "reaction/memory/memory_config.h"
#include <cstring>
#include <memory>

using namespace reaction;
using namespace reaction::memory;

// Test data structures for SBO testing
struct SmallStruct {
    int x, y;
    SmallStruct(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator==(const SmallStruct& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const SmallStruct& other) const {
        return !(*this == other);
    }
};

struct MediumStruct {
    double data[4];  // 32 bytes
    MediumStruct(double val = 0.0) {
        for (int i = 0; i < 4; ++i) data[i] = val + i;
    }
    bool operator==(const MediumStruct& other) const {
        for (int i = 0; i < 4; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }
    bool operator!=(const MediumStruct& other) const {
        return !(*this == other);
    }
};

struct LargeStruct {
    char data[128];  // 128 bytes - should force heap allocation
    LargeStruct(char fill = 'A') {
        std::fill(data, data + 128, fill);
    }
    bool operator==(const LargeStruct& other) const {
        return std::memcmp(data, other.data, 128) == 0;
    }
    bool operator!=(const LargeStruct& other) const {
        return !(*this == other);
    }
};

/**
 * Result structure for SBOTraitsBasicTypes test.
 */
struct SBOTraitsBasicTypesResult {
    bool int_is_sbo_eligible;
    bool int_always_sbo;
    bool int_conditional_sbo;

    bool double_is_sbo_eligible;
    bool double_always_sbo;

    bool smallstruct_is_sbo_eligible;
    bool smallstruct_always_sbo;

    bool mediumstruct_is_sbo_eligible;
    bool mediumstruct_always_sbo;
    bool mediumstruct_conditional_sbo;

    bool largestruct_is_sbo_eligible;
    bool largestruct_force_heap;

    bool string_force_heap;
    bool vector_force_heap;
};

/**
 * Function: collect SBOTraits properties for various types.
 */
SBOTraitsBasicTypesResult run_sbo_traits_basic_types() {
    SBOTraitsBasicTypesResult result{};

    result.int_is_sbo_eligible      = SBOTraits<int>::is_sbo_eligible;
    result.int_always_sbo           = SBOTraits<int>::always_sbo;
    result.int_conditional_sbo      = SBOTraits<int>::conditional_sbo;

    result.double_is_sbo_eligible   = SBOTraits<double>::is_sbo_eligible;
    result.double_always_sbo        = SBOTraits<double>::always_sbo;

    result.smallstruct_is_sbo_eligible = SBOTraits<SmallStruct>::is_sbo_eligible;
    result.smallstruct_always_sbo      = SBOTraits<SmallStruct>::always_sbo;

    result.mediumstruct_is_sbo_eligible   = SBOTraits<MediumStruct>::is_sbo_eligible;
    result.mediumstruct_always_sbo        = SBOTraits<MediumStruct>::always_sbo;
    result.mediumstruct_conditional_sbo   = SBOTraits<MediumStruct>::conditional_sbo;

    result.largestruct_is_sbo_eligible = SBOTraits<LargeStruct>::is_sbo_eligible;
    result.largestruct_force_heap      = SBOTraits<LargeStruct>::force_heap;

    result.string_force_heap = SBOTraits<std::string>::force_heap;
    result.vector_force_heap = SBOTraits<std::vector<int>>::force_heap;

    return result;
}

