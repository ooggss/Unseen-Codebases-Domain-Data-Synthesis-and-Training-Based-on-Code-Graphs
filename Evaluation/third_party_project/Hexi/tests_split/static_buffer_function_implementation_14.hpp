
#include <hexi/static_buffer.h>

#include <utility>

/**
 * @brief Advance the write cursor and write a byte, then return the resulting second element.
 *
 * Constructs a hexi::static_buffer<char, 3> with {'a','b','c'}, seeks write position to 0,
 * advances the write cursor by 1, writes 'd', then returns buffer[1] and the written value.
 *
 * @return std::pair<char, char>
 * - first: buffer[1] after the operation
 * - second: the value that was written ('d')
 */
std::pair<char, char> static_buffer_advance_write_impl() {
  hexi::static_buffer<char, 3> buffer{'a', 'b', 'c'};
  buffer.write_seek(hexi::buffer_seek::sk_absolute, 0);
  const char val = 'd';
  buffer.advance_write(1);
  buffer.write(&val, 1);
  return {buffer[1], val};
}
