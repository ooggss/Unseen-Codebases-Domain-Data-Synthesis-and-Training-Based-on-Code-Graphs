#pragma once

#include <cstddef>
#include <reaction/memory/memory_config.h>

namespace test_reaction {

struct TinyPod {
    int a;
    int b;
};

struct MediumPod {
    double values[3];  // 24 bytes
};

struct LargePod {
    std::byte payload[128];
};

struct SboTraitSummary {
    bool tinyAlwaysSbo;
    bool tinyForceHeap;
    bool mediumConditionalSbo;
    bool mediumForceHeap;
    bool largeForceHeap;
    std::size_t alwaysThreshold;
    std::size_t conditionalThreshold;
    std::size_t maxStackUsage;
};

inline SboTraitSummary analyze_sbo_traits() {
    using namespace reaction::memory;

    return SboTraitSummary{
        .tinyAlwaysSbo = SBOTraits<TinyPod>::always_sbo,
        .tinyForceHeap = SBOTraits<TinyPod>::force_heap,
        .mediumConditionalSbo = SBOTraits<MediumPod>::conditional_sbo,
        .mediumForceHeap = SBOTraits<MediumPod>::force_heap,
        .largeForceHeap = SBOTraits<LargePod>::force_heap,
        .alwaysThreshold = SBOConfig::ALWAYS_SBO_SIZE,
        .conditionalThreshold = SBOConfig::CONDITIONAL_SBO_SIZE,
        .maxStackUsage = SBOConfig::MAX_SBO_STACK_USAGE,
    };
}

}  // namespace test_reaction

