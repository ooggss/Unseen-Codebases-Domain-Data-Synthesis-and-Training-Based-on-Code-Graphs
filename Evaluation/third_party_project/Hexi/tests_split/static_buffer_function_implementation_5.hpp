
#include <hexi/static_buffer.h>

#include <cstddef>
#include <cstdint>
#include <utility>

/**
 * @brief Skip one byte then read one byte from a buffer and report state.
 *
 * Constructs a hexi::static_buffer<char, 3> with {'1','2','3'}, skips one byte,
 * then reads one byte into an 8-bit value. Returns:
 * - remaining buffer size
 * - buffer[0] after the operations (first unread byte)
 *
 * @return std::pair<std::size_t, char>
 * - first: buffer.size() after skip+read
 * - second: buffer[0] after skip+read
 */
std::pair<std::size_t, char> static_buffer_single_read_skip_impl() {
  hexi::static_buffer<char, 3> buffer{'1', '2', '3'};
  std::uint8_t value = 0;
  buffer.skip(1);
  buffer.read(&value, 1);
  return {buffer.size(), buffer[0]};
}
