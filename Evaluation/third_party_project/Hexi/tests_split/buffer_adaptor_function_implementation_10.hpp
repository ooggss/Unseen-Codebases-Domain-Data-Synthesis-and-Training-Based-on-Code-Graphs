

// Split from original test: buffer_adaptor.can_write_seek

#include <hexi/buffer_adaptor.h>
#include <vector>
#include <cstdint>

/**
 * @brief Determine whether buffer_adaptor supports write seeking for a std::vector<uint8_t>.
 *
 * This function models the functional portion of the original test case:
 * - Creates an empty vector and adaptor
 * - Returns adaptor.can_write_seek()
 *
 * @return bool
 * True if write seeking is supported (expected true for vector-backed adaptor).
 */
inline bool buffer_adaptor_can_write_seek() {
  std::vector<std::uint8_t> buffer;
  hexi::buffer_adaptor adaptor(buffer);
  return adaptor.can_write_seek();
}

