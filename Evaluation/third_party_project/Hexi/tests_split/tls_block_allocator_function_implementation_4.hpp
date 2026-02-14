
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <cstdint>
#include <thread>

#define HEXI_DEBUG_ALLOCATORS
#include <hexi/allocators/tls_block_allocator.h>

/**
 * Function: tls_block_allocator_thread_mismatch_death_triggers
 *
 * Allocates a chunk on the calling thread, then attempts to deallocate it from a
 * different thread, which is expected to terminate the process (death test).
 *
 * This function isolates the *operation under test* (cross-thread deallocation)
 * so the test can wrap it with ASSERT_DEATH.
 *
 * Note:
 * - The function intentionally does not catch/handle termination.
 * - It spawns a worker thread that performs the invalid deallocation.
 *
 * @param none
 * @return void This function does not return. Correct behavior is process termination
 *              when the cross-thread deallocation occurs.
 */
void tls_block_allocator_thread_mismatch_death_triggers() {
  hexi::tls_block_allocator<std::uint64_t, 1> tlsalloc;
  auto chunk = tlsalloc.allocate();

  std::jthread thread([&] {
    // Expected to abort/terminate inside the allocator due to thread mismatch.
    tlsalloc.deallocate(chunk);
  });

  // If the allocator does not terminate, ensure cleanup to avoid leaks (not expected).
  tlsalloc.deallocate(chunk);
}
