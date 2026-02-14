
#include <hexi/static_buffer.h>

#include <array>
#include <cstddef>
#include <tuple>

/**
 * @brief Exercise defragmentation behavior and capture key observations, including underrun.
 *
 * Steps performed:
 * 1) Create buffer {'a','b','c'} and record free() (expected 0).
 * 2) read 1 byte (expect 'a'), record free() again (expected 0).
 * 3) defragment(), record free() (expected 1).
 * 4) copy 1 byte into value (expect 'b'), and observe buffer[0] and *read_ptr() (expect 'b').
 * 5) read 'b', then read 'c'.
 * 6) Attempt another read and capture whether hexi::buffer_underrun was thrown.
 *
 * @return std::tuple<std::size_t, char, std::size_t, std::size_t, char, char, char, char, bool>
 * Elements:
 * 0: free() initially
 * 1: first read value ('a')
 * 2: free() after first read (before defragment)
 * 3: free() after defragment
 * 4: value after copy (expected 'b')
 * 5: buffer[0] after defragment (expected 'b')
 * 6: *read_ptr() after defragment (expected 'b')
 * 7: value after reading 'b' (expected 'b')
 * 8: value after reading 'c' (expected 'c')
 * 9: whether the final read threw hexi::buffer_underrun (expected true)
 */
std::tuple<std::size_t, char, std::size_t, std::size_t, char, char, char, char, char, bool>
static_buffer_defragment_impl() {
  hexi::static_buffer<char, 3> buffer{'a', 'b', 'c'};

  std::size_t free0 = buffer.free();

  char value = 0;
  buffer.read(&value, sizeof(value));
  char first_read = value;

  std::size_t free1 = buffer.free();

  buffer.defragment();
  std::size_t free2 = buffer.free();

  buffer.copy(&value, sizeof(value));
  char after_copy = value;

  char buf0 = buffer[0];
  char ptr0 = *buffer.read_ptr();

  buffer.read(&value, sizeof(value));
  char read_b = value;

  buffer.read(&value, sizeof(value));
  char read_c = value;

  bool threw = false;
  try {
    buffer.read(&value, sizeof(value));
  } catch (const hexi::buffer_underrun&) {
    threw = true;
  }

  return {free0, first_read, free1, free2, after_copy, buf0, ptr0, read_b, read_c, threw};
}
