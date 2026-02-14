
#include <hexi/static_buffer.h>

#include <cstddef>
#include <tuple>

/**
 * @brief Read a single byte from a pre-filled static buffer and report results.
 *
 * Constructs a hexi::static_buffer<char, 3> with {'1','2','3'}, reads one byte into
 * a local variable, then returns the remaining buffer size and the read value.
 *
 * @return std::pair<std::size_t, char>
 * - first: buffer.size() after reading one byte
 * - second: the value that was read
 */
std::pair<std::size_t, char> static_buffer_read_one_impl() {
  hexi::static_buffer<char, 3> buffer{'1', '2', '3'};
  char value = 0;
  buffer.read(&value, 1);
  return {buffer.size(), value};
}
