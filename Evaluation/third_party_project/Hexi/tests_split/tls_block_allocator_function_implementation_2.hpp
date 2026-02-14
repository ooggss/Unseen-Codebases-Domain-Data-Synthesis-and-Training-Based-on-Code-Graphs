
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <array>
#include <cstdint>

#define HEXI_DEBUG_ALLOCATORS
#include <hexi/allocators/tls_block_allocator.h>

/**
 * Function: tls_block_allocator_over_capacity_observe
 *
 * Exercises allocator behavior when allocating more chunks than the configured TLS
 * storage capacity (capacity=1). The first allocation should use TLS storage; the
 * second should fall back to a "new" allocation path tracked by `new_active_count`.
 *
 * Observes counters after:
 *  1) two allocations
 *  2) deallocating the first chunk
 *  3) deallocating the second chunk
 *
 * @param none
 * @return std::array<std::uint64_t, 12> A fixed-size array containing 3 checkpoints
 * (each with 4 values in order):
 *   - storage_active_count, new_active_count, total_allocs, total_deallocs
 * Checkpoints:
 *   [0..3]   after 2 allocs
 *   [4..7]   after dealloc mem[0]
 *   [8..11]  after dealloc mem[1]
 */
std::array<std::uint64_t, 12> tls_block_allocator_over_capacity_observe() {
  hexi::tls_block_allocator<std::uint64_t, 1> tlsalloc;

  std::array<std::uint64_t*, 2> mem{};
  mem[0] = tlsalloc.allocate();
  mem[1] = tlsalloc.allocate();

  const std::array<std::uint64_t, 4> after_two_allocs = {
      static_cast<std::uint64_t>(tlsalloc.allocator()->storage_active_count),
      static_cast<std::uint64_t>(tlsalloc.allocator()->new_active_count),
      static_cast<std::uint64_t>(tlsalloc.total_allocs),
      static_cast<std::uint64_t>(tlsalloc.total_deallocs),
  };

  tlsalloc.deallocate(mem[0]);

  const std::array<std::uint64_t, 4> after_dealloc0 = {
      static_cast<std::uint64_t>(tlsalloc.allocator()->storage_active_count),
      static_cast<std::uint64_t>(tlsalloc.allocator()->new_active_count),
      static_cast<std::uint64_t>(tlsalloc.total_allocs),
      static_cast<std::uint64_t>(tlsalloc.total_deallocs),
  };

  tlsalloc.deallocate(mem[1]);

  const std::array<std::uint64_t, 4> after_dealloc1 = {
      static_cast<std::uint64_t>(tlsalloc.allocator()->storage_active_count),
      static_cast<std::uint64_t>(tlsalloc.allocator()->new_active_count),
      static_cast<std::uint64_t>(tlsalloc.total_allocs),
      static_cast<std::uint64_t>(tlsalloc.total_deallocs),
  };

  return {
      after_two_allocs[0], after_two_allocs[1], after_two_allocs[2], after_two_allocs[3],
      after_dealloc0[0],   after_dealloc0[1],   after_dealloc0[2],   after_dealloc0[3],
      after_dealloc1[0],   after_dealloc1[1],   after_dealloc1[2],   after_dealloc1[3],
  };
}
