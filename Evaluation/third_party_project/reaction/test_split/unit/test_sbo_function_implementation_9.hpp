

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "reaction/memory/sbo_resource.h"
#include "reaction/memory/stack_monitor.h"
#include "reaction/memory/memory_config.h"
#include <memory>
#include <cstring>

using namespace reaction;
using namespace reaction::memory;

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
 * Structures mirroring StorageInfo (we assume SBOResource::getStorageInfo() returns this).
 */
struct SBOStorageInfoResult {
    bool sbo_using_sbo;
    bool sbo_initialized;
    std::size_t sbo_type_size;
    std::size_t sbo_stack_usage;

    bool heap_using_sbo;
    bool heap_initialized;
    std::size_t heap_type_size;
    std::size_t heap_stack_usage;
};

/**
 * Function: exercise storage info debugging for SBOResource with small and large types.
 */
SBOStorageInfoResult run_storage_info_debugging() {
    SBOStorageInfoResult r{};

    auto sbo_resource  = std::make_shared<SBOResource<SmallStruct>>(SmallStruct{1, 2});
    auto heap_resource = std::make_shared<SBOResource<LargeStruct>>(LargeStruct{'X'});

    auto sbo_info  = sbo_resource->getStorageInfo();
    auto heap_info = heap_resource->getStorageInfo();

    r.sbo_using_sbo   = sbo_info.using_sbo;
    r.sbo_initialized = sbo_info.initialized;
    r.sbo_type_size   = sbo_info.type_size;
    r.sbo_stack_usage = sbo_info.stack_usage;

    r.heap_using_sbo   = heap_info.using_sbo;
    r.heap_initialized = heap_info.initialized;
    r.heap_type_size   = heap_info.type_size;
    r.heap_stack_usage = heap_info.stack_usage;

    return r;
}

