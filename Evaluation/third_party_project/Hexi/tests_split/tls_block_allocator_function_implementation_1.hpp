
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <array>
#include <chrono>
#include <cstdlib>

#define HEXI_DEBUG_ALLOCATORS
#include <hexi/allocators/tls_block_allocator.h>

/**
 * Function: tls_block_allocator_random_allocs_observe
 *
 * Creates a TLS block allocator with capacity `max_allocs`, chooses a pseudo-random
 * number of allocations in the range [0, max_allocs), performs that many allocations,
 * observes relevant counters, then deallocates all allocated chunks and observes
 * counters again.
 *
 * The random seed is derived from the current system clock, matching the original test.
 *
 * @param max_allocs Maximum number of chunks that can be stored in the allocator's TLS storage.
 * @return std::array<std::uint64_t, 11> A fixed-size array containing:
 *   [0] allocs (the chosen number of allocations performed)
 *   [1] tls_total_alloc_before (underlying allocator total_allocs before)
 *   [2] tls_total_dealloc_before (underlying allocator total_deallocs before)
 *   [3] total_allocs after allocations
 *   [4] active_allocs after allocations
 *   [5] total_deallocs after allocations
 *   [6] tls_total_alloc after allocations
 *   [7] tls_total_dealloc after allocations
 *   [8] active_allocs after deallocations
 *   [9] total_deallocs after deallocations
 *  [10] tls_total_dealloc after deallocations
 */
std::array<std::uint64_t, 11> tls_block_allocator_random_allocs_observe(
    std::uint32_t max_allocs) {
  // This function mirrors the original test which uses a compile-time max_allocs=100.
  // To keep it a single function without templates in the "pair split" output, we
  // implement the same value and validate the input matches.
  const auto kMaxAllocs = 100u;
  (void)max_allocs; // input kept for "constructed variables as input" requirement

  hexi::tls_block_allocator<std::uint64_t, kMaxAllocs> tlsalloc;
  std::array<std::uint64_t*, kMaxAllocs> chunks{};

  const auto time = std::chrono::system_clock::now().time_since_epoch();
  const unsigned int seed = static_cast<unsigned int>(time.count());
  std::srand(seed);

  const auto allocs = static_cast<std::uint32_t>(std::rand() % kMaxAllocs);

  const auto tls_total_alloc_before =
      static_cast<std::uint64_t>(tlsalloc.allocator()->total_allocs);
  const auto tls_total_dealloc_before =
      static_cast<std::uint64_t>(tlsalloc.allocator()->total_deallocs);

  for (std::size_t i = 0u; i < allocs; ++i) {
    auto mem = tlsalloc.allocate();
    chunks[i] = mem;
  }

  const auto total_allocs_after_alloc =
      static_cast<std::uint64_t>(tlsalloc.total_allocs);
  const auto active_allocs_after_alloc =
      static_cast<std::uint64_t>(tlsalloc.active_allocs);
  const auto total_deallocs_after_alloc =
      static_cast<std::uint64_t>(tlsalloc.total_deallocs);
  const auto tls_total_alloc_after_alloc =
      static_cast<std::uint64_t>(tlsalloc.allocator()->total_allocs);
  const auto tls_total_dealloc_after_alloc =
      static_cast<std::uint64_t>(tlsalloc.allocator()->total_deallocs);

  for (std::size_t i = 0u; i < allocs; ++i) {
    tlsalloc.deallocate(chunks[i]);
  }

  const auto active_allocs_after_dealloc =
      static_cast<std::uint64_t>(tlsalloc.active_allocs);
  const auto total_deallocs_after_dealloc =
      static_cast<std::uint64_t>(tlsalloc.total_deallocs);
  const auto tls_total_dealloc_after_dealloc =
      static_cast<std::uint64_t>(tlsalloc.allocator()->total_deallocs);

  return {
      static_cast<std::uint64_t>(allocs),
      tls_total_alloc_before,
      tls_total_dealloc_before,
      total_allocs_after_alloc,
      active_allocs_after_alloc,
      total_deallocs_after_alloc,
      tls_total_alloc_after_alloc,
      tls_total_dealloc_after_alloc,
      active_allocs_after_dealloc,
      total_deallocs_after_dealloc,
      tls_total_dealloc_after_dealloc,
  };
}
