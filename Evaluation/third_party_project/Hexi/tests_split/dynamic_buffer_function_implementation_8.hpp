
// Function extracted from TEST(dynamic_buffer, copy)

#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <cstddef>
#include <tuple>

/**
 * Write an integer, copy it out without consuming, and report sizes and copied value.
 *
 * @param value Integer to write.
 * @return std::tuple<int, std::size_t, std::size_t>
 *   - Copied integer output
 *   - Size after write (expected sizeof(int))
 *   - Size after copy (expected unchanged, sizeof(int))
 */
std::tuple<int, std::size_t, std::size_t> dynamic_buffer_copy_does_not_consume(int value) {
  hexi::dynamic_buffer<32> chain;

  chain.write(&value, sizeof(int));
  const std::size_t size_after_write = chain.size();

  int output = 0;
  chain.copy(&output, sizeof(int));
  const std::size_t size_after_copy = chain.size();

  return {output, size_after_write, size_after_copy};
}
