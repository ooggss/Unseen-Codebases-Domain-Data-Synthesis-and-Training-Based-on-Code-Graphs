
#include <hexi/static_buffer.h>

#include <array>
#include <cstddef>
#include <utility>

/**
 * @brief Seek to the start (absolute position 0) and overwrite entire buffer, returning size and content.
 *
 * Constructs a hexi::static_buffer<char, 3> with {'1','2','3'}, seeks write position to 0,
 * writes {'4','5','6'}, then returns final size and contents.
 *
 * @return std::pair<std::size_t, std::array<char, 3>>
 * - first: buffer.size() after write
 * - second: final buffer contents
 */
std::pair<std::size_t, std::array<char, 3>> static_buffer_write_seek_start_impl() {
  hexi::static_buffer<char, 3> buffer{'1', '2', '3'};
  std::array<char, 3> values{'4', '5', '6'};
  buffer.write_seek(hexi::buffer_seek::sk_absolute, 0);
  buffer.write(values.data(), values.size());
  return {buffer.size(), {buffer[0], buffer[1], buffer[2]}};
}
