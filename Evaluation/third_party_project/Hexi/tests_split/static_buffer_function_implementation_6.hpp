
#include <hexi/static_buffer.h>

#include <cstddef>
#include <cstdint>
#include <utility>

/**
 * @brief Skip multiple bytes then read the last byte and report results.
 *
 * Constructs a hexi::static_buffer<char, 6> initialized with '1'..'6', skips 5 bytes,
 * then reads 1 byte. Returns whether the buffer is empty and the value that was read.
 *
 * @return std::pair<bool, char>
 * - first: buffer.empty() after skip+read
 * - second: the value read (as a char)
 */
std::pair<bool, char> static_buffer_multiskip_read_impl() {
  hexi::static_buffer<char, 6> buffer{'1', '2', '3', '4', '5', '6'};
  std::uint8_t value = 0;
  buffer.skip(5);
  buffer.read(&value, 1);
  return {buffer.empty(), static_cast<char>(value)};
}
