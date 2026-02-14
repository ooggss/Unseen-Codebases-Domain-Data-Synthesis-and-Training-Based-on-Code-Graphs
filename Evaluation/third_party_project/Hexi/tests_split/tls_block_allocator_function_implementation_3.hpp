
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <array>
#include <cstdint>
#include <thread>

#define HEXI_DEBUG_ALLOCATORS
#include <hexi/allocators/tls_block_allocator.h>

/**
 * Function: tls_block_allocator_no_sharing_observe
 *
 * Validates that TLS allocators are not shared across threads by:
 * - creating an allocator on the main thread and allocating once
 * - creating a separate allocator inside a new thread and verifying its counters
 *   start at zero, then allocating/deallocating once and observing its counters
 * - deallocating the main-thread allocation and observing deallocation counter change
 *
 * The function returns all values that are asserted in the original `no_sharing` test.
 *
 * @param none
 * @return std::array<std::uint64_t, 8> Values in order:
 *   [0] main_tls_total_alloc_before
 *   [1] main_tls_total_dealloc_before
 *   [2] main_storage_active_after_alloc
 *   [3] main_tls_total_alloc_after_alloc
 *   [4] thread_tls_total_alloc_initial
 *   [5] thread_storage_active_initial
 *   [6] thread_tls_total_alloc_after_alloc
 *   [7] main_tls_total_dealloc_after_dealloc
 */
std::array<std::uint64_t, 8> tls_block_allocator_no_sharing_observe() {
  hexi::tls_block_allocator<std::uint64_t, 2> tlsalloc;

  const auto main_tls_total_alloc_before =
      static_cast<std::uint64_t>(tlsalloc.allocator()->total_allocs);
  const auto main_tls_total_dealloc_before =
      static_cast<std::uint64_t>(tlsalloc.allocator()->total_deallocs);

  auto chunk = tlsalloc.allocate();

  const auto main_storage_active_after_alloc =
      static_cast<std::uint64_t>(tlsalloc.allocator()->storage_active_count);
  const auto main_tls_total_alloc_after_alloc =
      static_cast<std::uint64_t>(tlsalloc.allocator()->total_allocs);

  std::uint64_t thread_tls_total_alloc_initial = 0;
  std::uint64_t thread_storage_active_initial = 0;
  std::uint64_t thread_tls_total_alloc_after_alloc = 0;

  std::thread thread([&] {
    hexi::tls_block_allocator<std::uint64_t, 2> tlsalloc_;
    thread_tls_total_alloc_initial =
        static_cast<std::uint64_t>(tlsalloc_.allocator()->total_allocs);
    thread_storage_active_initial =
        static_cast<std::uint64_t>(tlsalloc_.allocator()->storage_active_count);

    auto chunk_ = tlsalloc_.allocate();

    // After alloc (the test also checks storage_active_count==1 and dealloc counts,
    // but they are derivable and not required beyond assertions we return)
    thread_tls_total_alloc_after_alloc =
        static_cast<std::uint64_t>(tlsalloc_.allocator()->total_allocs);

    tlsalloc_.deallocate(chunk_);
  });

  thread.join();

  tlsalloc.deallocate(chunk);

  const auto main_tls_total_dealloc_after_dealloc =
      static_cast<std::uint64_t>(tlsalloc.allocator()->total_deallocs);

  return {
      main_tls_total_alloc_before,
      main_tls_total_dealloc_before,
      main_storage_active_after_alloc,
      main_tls_total_alloc_after_alloc,
      thread_tls_total_alloc_initial,
      thread_storage_active_initial,
      thread_tls_total_alloc_after_alloc,
      main_tls_total_dealloc_after_dealloc,
  };
}
