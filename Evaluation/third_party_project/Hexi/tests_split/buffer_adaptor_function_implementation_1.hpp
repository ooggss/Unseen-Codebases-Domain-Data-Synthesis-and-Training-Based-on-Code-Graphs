

// Split from original test: buffer_adaptor.empty

#include <hexi/buffer_adaptor.h>
#include <vector>
#include <cstdint>
#include <utility>

/**
 * @brief Check adaptor empty-state before and after a single-byte write advance.
 *
 * This function models the functional portion of the original test case:
 * - Creates an empty std::vector<uint8_t> and a buffer_adaptor over it
 * - Records whether adaptor.empty() is true initially
 * - Appends one byte to the underlying buffer and advances write position by 1
 * - Records whether adaptor.empty() is true after the advance
 *
 * @return std::pair<bool, bool>
 * - first: empty state immediately after construction (expected true)
 * - second: empty state after emplace_back + advance_write(1) (expected false)
 */
std::pair<bool, bool> buffer_adaptor_empty_before_after_write_advance() {
  std::vector<std::uint8_t> buffer;
  hexi::buffer_adaptor adaptor(buffer);

  const bool empty_initial = adaptor.empty();

  buffer.emplace_back(1);
  adaptor.advance_write(1);

  const bool empty_after = adaptor.empty();
  return {empty_initial, empty_after};
}

