#pragma once

#include <array>
#include <cstddef>
#include <reaction/memory/sbo_resource.h>

namespace test_reaction {

struct SmallPayload {
    int value;
    bool operator!=(const SmallPayload& other) const = default;
};

struct LargePayload {
    std::array<int, 64> data{};
    bool operator!=(const LargePayload& other) const = default;
};

struct SboStorageStatus {
    bool updateReportedChange;
    bool smallUsingSBO;
    std::size_t smallStackUsage;
    bool largeInitialized;
    bool largeUsingSBO;
};

/**
 * Function: Inspect SBOResource storage choices for small vs large payloads.
 *
 * @param initialSmall Initial value for the small payload
 * @param updatedSmall Updated value for the small payload
 * @param largeSeed Seed used to initialize the large payload contents
 * @return SboStorageStatus Snapshot containing storage mode observations
 */
inline SboStorageStatus test_sbo_storage_info(int initialSmall,
                                              int updatedSmall,
                                              int largeSeed) {
    using reaction::memory::SBOResource;

    auto makeLargePayload = [largeSeed]() {
        LargePayload payload;
        for (std::size_t i = 0; i < payload.data.size(); ++i) {
            payload.data[i] = largeSeed + static_cast<int>(i);
        }
        return payload;
    };

    SBOResource<SmallPayload> smallResource(SmallPayload{initialSmall});
    SBOResource<LargePayload> largeResource(makeLargePayload());

    const bool changeReported = smallResource.updateValue(SmallPayload{updatedSmall});

    const auto smallInfo = smallResource.getStorageInfo();
    const auto largeInfo = largeResource.getStorageInfo();

    return SboStorageStatus{
        .updateReportedChange = changeReported,
        .smallUsingSBO = smallInfo.using_sbo,
        .smallStackUsage = smallInfo.stack_usage,
        .largeInitialized = largeInfo.initialized,
        .largeUsingSBO = largeInfo.using_sbo,
    };
}

}  // namespace test_reaction

