

// Split from original test: buffer_adaptor.resize_match

#include <hexi/buffer_adaptor.h>
#include <vector>
#include <cstdint>
#include <utility>

/**
 * @brief Verify adaptor size tracks underlying vector size after growth and write-advance.
 *
 * This function models the functional portion of the original test case:
 * - Creates a vector with initial content and a buffer_adaptor over it
 * - Captures adaptor.size() and buffer.size() initially
 * - Grows the vector by one byte and calls adaptor.advance_write(1)
 * - Captures adaptor.size() and buffer.size() after the growth/advance
 *
 * @return std::pair<std::pair<std::size_t, std::size_t>, std::pair<std::size_t, std::size_t>>
 * - first pair: {adaptor_size_initial, buffer_size_initial}
 * - second pair: {adaptor_size_after, buffer_size_after}
 */
inline std::pair<std::pair<std::size_t, std::size_t>, std::pair<std::size_t, std::size_t>>
buffer_adaptor_resize_match_sizes() {
  std::vector<std::uint8_t> buffer{1, 2, 3, 4, 5};
  hexi::buffer_adaptor adaptor(buffer);

  const auto initial = std::pair{adaptor.size(), buffer.size()};

  buffer.emplace_back(6);
  adaptor.advance_write(1);

  const auto after = std::pair{adaptor.size(), buffer.size()};
  return {initial, after};
}

