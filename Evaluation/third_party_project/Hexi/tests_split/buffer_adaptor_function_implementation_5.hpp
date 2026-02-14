

// Split from original test: buffer_adaptor.read_all

#include <hexi/buffer_adaptor.h>
#include <array>
#include <cstdint>
#include <utility>

/**
 * @brief Read all bytes from a buffer_adaptor into an output array and return both arrays.
 *
 * This function models the functional portion of the original test case:
 * - Creates a std::array<uint8_t, 3> source buffer {1,2,3}
 * - Reads all bytes into another std::array<uint8_t, 3>
 * - Returns both the original buffer and the read-back values for comparison
 *
 * @return std::pair<std::array<std::uint8_t, 3>, std::array<std::uint8_t, 3>>
 * - first: the original buffer contents
 * - second: the values read from the adaptor
 */
inline std::pair<std::array<std::uint8_t, 3>, std::array<std::uint8_t, 3>> buffer_adaptor_read_all_values() {
  std::array<std::uint8_t, 3> buffer{1, 2, 3};
  hexi::buffer_adaptor adaptor(buffer);

  std::array<std::uint8_t, 3> values{};
  adaptor.read(&values, values.size());

  return {buffer, values};
}

