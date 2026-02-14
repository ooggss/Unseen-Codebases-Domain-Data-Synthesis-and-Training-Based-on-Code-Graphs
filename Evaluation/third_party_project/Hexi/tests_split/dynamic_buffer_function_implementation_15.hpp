
// Function extracted from TEST(dynamic_buffer, find_first_of)

#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <cstddef>
#include <string_view>
#include <tuple>

/**
 * Write a string_view into a dynamic_buffer and query find_first_of for several bytes.
 *
 * @param str Input text to write (note: not null-terminated in the buffer).
 * @param needle0 First byte to search for.
 * @param needle1 Second byte to search for.
 * @param needle2 Third byte to search for.
 * @param needle3 Fourth byte to search for.
 * @return std::tuple<std::size_t, std::size_t, std::size_t, std::size_t>
 *   Positions of each needle in the buffer in the same order as provided.
 *   The first position is expected to be dynamic_buffer::npos when searching for '\0'.
 */
std::tuple<std::size_t, std::size_t, std::size_t, std::size_t> dynamic_buffer_find_first_of_positions(
    std::string_view str,
    std::byte needle0,
    std::byte needle1,
    std::byte needle2,
    std::byte needle3) {
  hexi::dynamic_buffer<64> buffer;
  buffer.write(str.data(), str.size());

  const auto p0 = buffer.find_first_of(needle0);
  const auto p1 = buffer.find_first_of(needle1);
  const auto p2 = buffer.find_first_of(needle2);
  const auto p3 = buffer.find_first_of(needle3);

  return {p0, p1, p2, p3};
}
