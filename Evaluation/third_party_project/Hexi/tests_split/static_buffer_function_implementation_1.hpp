
#include <hexi/static_buffer.h>

#include <cstddef>
#include <utility>

/**
 * @brief Construct a static_buffer<char, 2> pre-filled with two characters and query its state.
 *
 * Creates a hexi::static_buffer<char, 2> initialized with {'1','2'} and returns:
 * - whether it is empty
 * - its size
 * - the first and second elements via operator[]
 *
 * @return std::tuple<bool, std::size_t, char, char>
 * - empty flag, size, element[0], element[1]
 */
std::tuple<bool, std::size_t, char, char> static_buffer_initial_not_empty_impl() {
  hexi::static_buffer<char, 2> buffer{'1', '2'};
  return {buffer.empty(), buffer.size(), buffer[0], buffer[1]};
}
