

// Split from original test: buffer_adaptor.read_one

#include <hexi/buffer_adaptor.h>
#include <array>
#include <cstdint>
#include <utility>

/**
 * @brief Read one byte from a buffer_adaptor and return remaining size and value read.
 *
 * This function models the functional portion of the original test case:
 * - Creates a std::array<uint8_t, 3> with values {1,2,3}
 * - Reads one byte via adaptor.read(&value, 1)
 * - Returns adaptor.size() after the read and the value that was read
 *
 * @return std::pair<std::size_t, std::uint8_t>
 * - first: adaptor.size() after reading one byte (expected buffer.size()-1)
 * - second: the byte read (expected 1)
 */
inline std::pair<std::size_t, std::uint8_t> buffer_adaptor_read_one_result() {
  std::array<std::uint8_t, 3> buffer{1, 2, 3};
  hexi::buffer_adaptor adaptor(buffer);

  std::uint8_t value = 0;
  adaptor.read(&value, 1);

  return {adaptor.size(), value};
}

