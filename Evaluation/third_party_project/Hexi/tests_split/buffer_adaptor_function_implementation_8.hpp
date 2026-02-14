

// Split from original test: buffer_adaptor.write

#include <hexi/buffer_adaptor.h>
#include <vector>
#include <array>
#include <ranges>
#include <cstdint>

/**
 * @brief Write a sequence of bytes into an initially empty buffer, then write one extra byte.
 *
 * This function models the functional portion of the original test case:
 * - Creates an empty std::vector<uint8_t> and adaptor
 * - Writes 6 bytes {1..6}
 * - Captures adaptor.size(), buffer.size(), and equality to written values
 * - Writes one additional byte '\\0'
 * - Captures adaptor.size() after the extra write
 *
 * @return struct WriteOutcome
 * Aggregated results used by the test assertions.
 */
struct WriteOutcome {
  std::size_t adaptor_size_after_block_write;
  std::size_t buffer_size_after_block_write;
  bool buffer_equals_values_after_block_write;
  std::size_t adaptor_size_after_single_write;
};

WriteOutcome buffer_adaptor_write_outcome() {
  std::vector<std::uint8_t> buffer;
  hexi::buffer_adaptor adaptor(buffer);

  std::array<std::uint8_t, 6> values{1, 2, 3, 4, 5, 6};
  adaptor.write(values.data(), values.size());

  const auto size_after_block = adaptor.size();
  const auto buffer_size_after_block = buffer.size();
  const bool equals_after_block = std::ranges::equal(values, buffer);

  adaptor.write('\0');
  const auto size_after_single = adaptor.size();

  return WriteOutcome{
      .adaptor_size_after_block_write = size_after_block,
      .buffer_size_after_block_write = buffer_size_after_block,
      .buffer_equals_values_after_block_write = equals_after_block,
      .adaptor_size_after_single_write = size_after_single,
  };
}

