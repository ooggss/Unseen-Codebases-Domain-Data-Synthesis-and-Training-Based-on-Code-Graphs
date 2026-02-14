
// Function extracted from TEST(dynamic_buffer, clear)

#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <cstddef>
#include <tuple>

/**
 * Write a sequence of integers to the buffer, then clear it and report state.
 *
 * @param iterations Number of integers (0..iterations-1) to write.
 * @return std::tuple<std::size_t, std::size_t, bool, std::size_t>
 *   - size before clear (expected sizeof(int) * iterations)
 *   - size after clear (expected 0)
 *   - empty() after clear (expected true)
 *   - block_count() after clear (expected 0)
 */
std::tuple<std::size_t, std::size_t, bool, std::size_t> dynamic_buffer_write_then_clear(
    int iterations) {
  hexi::dynamic_buffer<32> chain;

  for (int i = 0; i < iterations; ++i) {
    chain.write(&i, sizeof(int));
  }

  const std::size_t size_before = chain.size();
  chain.clear();
  const std::size_t size_after = chain.size();
  const bool is_empty = chain.empty();
  const std::size_t blocks = chain.block_count();

  return {size_before, size_after, is_empty, blocks};
}
