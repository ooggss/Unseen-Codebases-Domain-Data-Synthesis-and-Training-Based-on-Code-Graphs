
#include <hexi/static_buffer.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

/**
 * @brief Write a fixed array of bytes into a static_buffer and return the buffer contents and size.
 *
 * Constructs an empty hexi::static_buffer<std::uint8_t, 6>, writes {1,2,3,4,5,6}
 * into it, then returns:
 * - the resulting size
 * - the resulting contents copied into a std::array<uint8_t, 6>
 *
 * @return std::pair<std::size_t, std::array<std::uint8_t, 6>>
 * - first: buffer.size() after writing
 * - second: a copy of the buffer contents
 */
std::pair<std::size_t, std::array<std::uint8_t, 6>> static_buffer_write_impl() {
  hexi::static_buffer<std::uint8_t, 6> buffer;
  const std::array<std::uint8_t, 6> values{1, 2, 3, 4, 5, 6};
  buffer.write(values.data(), values.size());

  std::array<std::uint8_t, 6> out{};
  for (std::size_t i = 0; i < out.size(); ++i) out[i] = buffer[i];
  return {buffer.size(), out};
}
