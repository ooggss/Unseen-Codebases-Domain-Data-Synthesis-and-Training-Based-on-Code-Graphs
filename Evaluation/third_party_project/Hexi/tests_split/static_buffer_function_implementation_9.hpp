
#include <hexi/static_buffer.h>

#include <array>

/**
 * @brief Seek the write position backward and overwrite data, returning final buffer contents.
 *
 * Constructs a hexi::static_buffer<char, 3> with {'1','2','3'}, seeks the write cursor
 * backward by 2, then writes {'5','6'}. Returns the resulting buffer contents.
 *
 * @return std::array<char, 3> Final buffer content after the overwrite.
 */
std::array<char, 3> static_buffer_write_seek_back_impl() {
  hexi::static_buffer<char, 3> buffer{'1', '2', '3'};
  std::array<char, 2> values{'5', '6'};
  buffer.write_seek(hexi::buffer_seek::sk_backward, 2);
  buffer.write(values.data(), values.size());

  return {buffer[0], buffer[1], buffer[2]};
}
