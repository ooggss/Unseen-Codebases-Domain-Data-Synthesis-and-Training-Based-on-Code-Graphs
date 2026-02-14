
#include <hexi/static_buffer.h>

#include <cstddef>
#include <utility>

/**
 * @brief Verify that writing one byte to an initially empty buffer makes it non-empty.
 *
 * Constructs a hexi::static_buffer<char, 1>, records empty() before writing,
 * writes a single null character, then records empty() after writing.
 *
 * @return std::pair<bool, bool>
 * - first: empty() before write
 * - second: empty() after write
 */
std::pair<bool, bool> static_buffer_empty_after_write_impl() {
  hexi::static_buffer<char, 1> buffer;
  const bool before = buffer.empty();
  char val = '\0';
  buffer.write(&val, 1);
  const bool after = buffer.empty();
  return {before, after};
}
