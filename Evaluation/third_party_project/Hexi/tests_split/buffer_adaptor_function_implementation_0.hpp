

// Split from original test: buffer_adaptor.size_empty_initial

#include <hexi/buffer_adaptor.h>
#include <array>
#include <cstdint>

/**
 * @brief Construct a buffer_adaptor over an empty fixed-size array and return its initial size.
 *
 * This function models the functional portion of the original test case:
 * - Creates a std::array<uint8_t, 0>
 * - Wraps it in hexi::buffer_adaptor
 * - Returns adaptor.size()
 *
 * @return std::size_t
 * The initial size reported by the adaptor (expected to be 0 for an empty array).
 */
inline std::size_t buffer_adaptor_size_empty_initial() {
  std::array<std::uint8_t, 0> buffer;
  hexi::buffer_adaptor adaptor(buffer);
  return adaptor.size();
}

