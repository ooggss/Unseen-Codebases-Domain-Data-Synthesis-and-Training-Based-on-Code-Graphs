
#include <hexi/static_buffer.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <span>
#include <string_view>
#include <vector>

/**
 * @brief Construct an empty static_buffer<char, 1> and query its initial state.
 *
 * This function exists to isolate the "arrange/act" portion of the original test.
 * It constructs a hexi::static_buffer with capacity 1 and returns whether it is
 * initially empty as well as its initial size.
 *
 * @return std::pair<bool, std::size_t>
 * - first: result of buffer.empty()
 * - second: result of buffer.size()
 */
std::pair<bool, std::size_t> static_buffer_initial_empty_impl() {
  hexi::static_buffer<char, 1> buffer;
  return {buffer.empty(), buffer.size()};
}
