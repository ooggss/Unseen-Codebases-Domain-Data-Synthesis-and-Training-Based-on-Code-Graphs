
#include <hexi/static_buffer.h>

#include <array>

/**
 * @brief Exercise operator[] reads and writes and return observed values.
 *
 * Constructs a hexi::static_buffer<char, 3> with {'1','2','3'} and records:
 * - initial [0],[1],[2]
 * - value after setting buffer[0] = '4'
 * - value after setting buffer[0] = '5'
 * - value of buffer[0] compared to itself
 *
 * @return std::array<char, 6>
 * Indices:
 * 0: initial buffer[0]
 * 1: initial buffer[1]
 * 2: initial buffer[2]
 * 3: buffer[0] after set to '4'
 * 4: buffer[0] after set to '5'
 * 5: buffer[0] (final; useful for equality-to-self check)
 */
std::array<char, 6> static_buffer_subscript_impl() {
  hexi::static_buffer<char, 3> buffer{'1', '2', '3'};
  std::array<char, 6> out{};
  out[0] = buffer[0];
  out[1] = buffer[1];
  out[2] = buffer[2];

  buffer[0] = '4';
  out[3] = buffer[0];

  buffer[0] = '5';
  out[4] = buffer[0];

  out[5] = buffer[0];
  return out;
}
