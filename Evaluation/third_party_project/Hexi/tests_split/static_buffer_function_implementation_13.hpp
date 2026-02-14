
#include <hexi/static_buffer.h>

#include <cstddef>
#include <string_view>

using namespace std::literals;

/**
 * @brief Write a string into the buffer and query find_first_of for several characters.
 *
 * Writes "The quick brown fox jumped over the lazy dog" into a
 * hexi::static_buffer<char, 64> (without NUL terminator) and returns positions for:
 * - '\0' (should be npos because the write isn't terminated)
 * - 'g', 'T', 't'
 *
 * @return std::array<std::size_t, 4>
 * Indices:
 * 0: position of '\0'
 * 1: position of 'g'
 * 2: position of 'T'
 * 3: position of 't'
 */
std::array<std::size_t, 4> static_buffer_find_first_of_impl() {
  hexi::static_buffer<char, 64> buffer;
  const auto str = "The quick brown fox jumped over the lazy dog"sv;
  buffer.write(str.data(), str.size());

  return {buffer.find_first_of('\0'),
          buffer.find_first_of('g'),
          buffer.find_first_of('T'),
          buffer.find_first_of('t')};
}
