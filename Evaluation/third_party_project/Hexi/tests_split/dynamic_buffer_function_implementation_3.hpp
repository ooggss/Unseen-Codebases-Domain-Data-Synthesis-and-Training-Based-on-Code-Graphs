
// Function extracted from TEST(dynamic_buffer, skip)

#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <cstddef>
#include <utility>

/**
 * Write two integers, skip the first, then read the second.
 *
 * @param foo First integer to write.
 * @param bar Second integer to write.
 * @return std::pair<int, std::size_t>
 *   - The integer read after skipping (should equal bar)
 *   - Remaining chain size after read (should be 0)
 */
std::pair<int, std::size_t> dynamic_buffer_skip_then_read(int foo, int bar) {
  hexi::dynamic_buffer<32> chain;

  chain.write(&foo, sizeof(int));
  chain.write(&bar, sizeof(int));

  chain.skip(sizeof(int));

  int out = 0;
  chain.read(&out, sizeof(int));

  return {out, chain.size()};
}
