

// Split from original test: buffer_adaptor.size_populated_initial

#include <hexi/buffer_adaptor.h>
#include <array>
#include <cstdint>
#include <utility>

/**
 * @brief Construct a buffer_adaptor over a populated fixed-size array and return sizes.
 *
 * This function models the functional portion of the original test case:
 * - Creates a std::array<uint8_t, 1> initialized with one value
 * - Wraps it in hexi::buffer_adaptor
 * - Returns both adaptor.size() and buffer.size()
 *
 * @return std::pair<std::size_t, std::size_t>
 * - first: adaptor.size() after construction
 * - second: underlying buffer.size()
 */
inline std::pair<std::size_t, std::size_t> buffer_adaptor_size_populated_initial() {
  std::array<std::uint8_t, 1> buffer{1};
  hexi::buffer_adaptor adaptor(buffer);
  return {adaptor.size(), buffer.size()};
}

