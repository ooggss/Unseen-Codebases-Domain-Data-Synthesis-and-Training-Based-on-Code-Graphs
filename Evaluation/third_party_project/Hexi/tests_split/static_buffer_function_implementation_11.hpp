
#include <hexi/static_buffer.h>

#include <array>

/**
 * @brief Exercise read_ptr() as the buffer read position advances.
 *
 * Constructs a hexi::static_buffer<char, 3> with {'1','2','3'} and, after each skip(1),
 * captures the dereferenced read_ptr() and the current buffer[0]. Returns three pairs
 * (one per step) so the test can verify pointer value matches the front element.
 *
 * @return std::array<std::pair<char, char>, 3>
 * Each element is { *read_ptr(), buffer[0] } observed at that step.
 */
std::array<std::pair<char, char>, 3> static_buffer_read_ptr_impl() {
  hexi::static_buffer<char, 3> buffer{'1', '2', '3'};

  std::array<std::pair<char, char>, 3> observations{};

  auto ptr = buffer.read_ptr();
  observations[0] = {*ptr, buffer[0]};

  buffer.skip(1);
  ptr = buffer.read_ptr();
  observations[1] = {*ptr, buffer[0]};

  buffer.skip(1);
  ptr = buffer.read_ptr();
  observations[2] = {*ptr, buffer[0]};

  return observations;
}
