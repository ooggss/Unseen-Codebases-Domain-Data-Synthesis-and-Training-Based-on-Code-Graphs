
#include <hexi/static_buffer.h>

/**
 * @brief Check whether a static_buffer supports write seeking.
 *
 * Constructs a hexi::static_buffer<char, 1> and returns buffer.can_write_seek().
 *
 * @return bool True if write seeking is supported.
 */
bool static_buffer_can_write_seek_impl() {
  hexi::static_buffer<char, 1> buffer;
  return buffer.can_write_seek();
}
