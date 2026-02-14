

// Split from original test: buffer_adaptor.multiskip_read

#include <hexi/buffer_adaptor.h>
#include <array>
#include <cstdint>
#include <utility>

/**
 * @brief Skip multiple bytes, then read final byte; return empty-state and read value.
 *
 * This function models the functional portion of the original test case:
 * - Creates buffer {1,2,3,4,5,6}
 * - Uses hexi::buffer_adaptor<decltype(buffer), false>
 * - Skips 5 bytes, then reads 1 byte
 * - Returns adaptor.empty() and the read byte
 *
 * @return std::pair<bool, std::uint8_t>
 * - first: whether adaptor is empty after the read (expected true)
 * - second: value read (expected buffer[5] == 6)
 */
std::pair<bool, std::uint8_t> buffer_adaptor_multiskip_then_read() {
  std::array<std::uint8_t, 6> buffer{1, 2, 3, 4, 5, 6};
  hexi::buffer_adaptor<decltype(buffer), false> adaptor(buffer);

  std::uint8_t value = 0;
  adaptor.skip(5);
  adaptor.read(&value, 1);

  return {adaptor.empty(), value};
}

