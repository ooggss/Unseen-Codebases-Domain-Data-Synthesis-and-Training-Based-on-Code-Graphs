
#include <hexi/static_buffer.h>

#include <cstddef>
#include <tuple>

/**
 * @brief Track free space while writing into a fixed-size buffer and detect overflow exception.
 *
 * Constructs an empty hexi::static_buffer<char, 3>, then writes 1 byte three times, recording
 * free() after each write. Then attempts a fourth write and records whether
 * hexi::buffer_overflow was thrown.
 *
 * @return std::tuple<std::size_t, std::size_t, std::size_t, std::size_t, bool>
 * Elements:
 * 0: free() initially (expected 3)
 * 1: free() after first write (expected 2)
 * 2: free() after second write (expected 1)
 * 3: free() after third write (expected 0)
 * 4: whether the fourth write threw hexi::buffer_overflow (expected true)
 */
std::tuple<std::size_t, std::size_t, std::size_t, std::size_t, bool> static_buffer_free_buff_impl() {
  hexi::static_buffer<char, 3> buffer;
  std::size_t f0 = buffer.free();

  char value = 0;
  buffer.write(&value, sizeof(value));
  std::size_t f1 = buffer.free();

  buffer.write(&value, sizeof(value));
  std::size_t f2 = buffer.free();

  buffer.write(&value, sizeof(value));
  std::size_t f3 = buffer.free();

  bool threw = false;
  try {
    buffer.write(&value, sizeof(value));
  } catch (const hexi::buffer_overflow&) {
    threw = true;
  }

  return {f0, f1, f2, f3, threw};
}
