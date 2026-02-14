
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <array>
#include <chrono>
#include <cstdlib>
#include <thread>

#define HEXI_DEBUG_ALLOCATORS
#include <hexi/allocators/tls_block_allocator.h>

/**
 * Function: tls_block_allocator_single_alloc_observe
 *
 * Performs a single allocation and deallocation using a thread-local storage (TLS)
 * block allocator and returns allocator counter values observed at two checkpoints:
 *  1) immediately after allocation
 *  2) immediately after deallocation
 *
 * This mirrors the logic in the original `single_alloc` test:
 * - allocate one chunk
 * - read internal allocator counters and public counters
 * - deallocate the chunk
 * - read counters again
 *
 * @param none
 * @return std::array<std::uint64_t, 8> A fixed-size array containing:
 *   [0] storage_active_count after allocate
 *   [1] new_active_count after allocate
 *   [2] total_allocs after allocate
 *   [3] total_deallocs after allocate
 *   [4] storage_active_count after deallocate
 *   [5] new_active_count after deallocate
 *   [6] total_allocs after deallocate
 *   [7] total_deallocs after deallocate
 */
std::array<std::uint64_t, 8> tls_block_allocator_single_alloc_observe() {
  hexi::tls_block_allocator<std::uint64_t, 1> tlsalloc;

  auto mem = tlsalloc.allocate();

  const std::array<std::uint64_t, 4> after_alloc = {
      static_cast<std::uint64_t>(tlsalloc.allocator()->storage_active_count),
      static_cast<std::uint64_t>(tlsalloc.allocator()->new_active_count),
      static_cast<std::uint64_t>(tlsalloc.total_allocs),
      static_cast<std::uint64_t>(tlsalloc.total_deallocs),
  };

  tlsalloc.deallocate(mem);

  const std::array<std::uint64_t, 4> after_dealloc = {
      static_cast<std::uint64_t>(tlsalloc.allocator()->storage_active_count),
      static_cast<std::uint64_t>(tlsalloc.allocator()->new_active_count),
      static_cast<std::uint64_t>(tlsalloc.total_allocs),
      static_cast<std::uint64_t>(tlsalloc.total_deallocs),
  };

  return {after_alloc[0], after_alloc[1], after_alloc[2], after_alloc[3],
          after_dealloc[0], after_dealloc[1], after_dealloc[2], after_dealloc[3]};
}
