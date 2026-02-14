
// Function extracted from TEST(dynamic_buffer, empty)

#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <cstddef>
#include <tuple>

/**
 * Check empty() state before and after writing a value.
 *
 * @param value Integer value to write.
 * @return std::tuple<bool, bool>
 *   - empty() before write
 *   - empty() after write
 */
std::tuple<bool, bool> dynamic_buffer_empty_before_after_write(int value) {
  hexi::dynamic_buffer<32> chain;
  const bool before = chain.empty();
  chain.write(&value, sizeof(value));
  const bool after = chain.empty();
  return {before, after};
}
