
#include <hexi/static_buffer.h>

#include <array>
#include <cstddef>

/**
 * @brief Read all bytes from a pre-filled buffer into an array.
 *
 * Constructs a hexi::static_buffer<char, 3> with {'1','2','3'} and reads all
 * bytes into a std::array<char,3>, which is returned to the caller.
 *
 * @return std::array<char, 3> The bytes read from the buffer, in order.
 */
std::array<char, 3> static_buffer_read_all_impl() {
  hexi::static_buffer<char, 3> buffer{'1', '2', '3'};
  std::array<char, 3> values{};
  buffer.read(values.data(), values.size());
  return values;
}
