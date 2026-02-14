

// Split from original test: buffer_adaptor.single_skip_read

#include <hexi/buffer_adaptor.h>
#include <array>
#include <cstdint>
#include <utility>

/**
 * @brief Skip one byte, then read one byte; return remaining size and read value.
 *
 * This function models the functional portion of the original test case:
 * - Creates buffer {1,2,3}
 * - Calls adaptor.skip(1)
 * - Reads one byte into value
 * - Returns adaptor.size() and the read value
 *
 * @return std::pair<std::size_t, std::uint8_t>
 * - first: remaining adaptor size (expected 1)
 * - second: value read after skipping first byte (expected buffer[1] == 2)
 */
std::pair<std::size_t, std::uint8_t> buffer_adaptor_single_skip_then_read() {
  std::array<std::uint8_t, 3> buffer{1, 2, 3};
  hexi::buffer_adaptor adaptor(buffer);

  std::uint8_t value = 0;
  adaptor.skip(1);
  adaptor.read(&value, 1);

  return {adaptor.size(), value};
}

