

// Split from original test: buffer_adaptor.write_seek_start

#include <hexi/buffer_adaptor.h>
#include <vector>
#include <array>
#include <ranges>
#include <cstdint>

/**
 * @brief Seek to absolute start and write data; return final state for verification.
 *
 * This function models the functional portion of the original test case:
 * - Starts with buffer {1,2,3}
 * - Seeks to absolute position 0
 * - Writes {4,5,6}
 * - Expects buffer equals {4,5,6}
 *
 * @return struct SeekStartOutcome
 * Aggregated results used by the test assertions.
 */
struct SeekStartOutcome {
  std::size_t buffer_size;
  std::size_t adaptor_size;
  bool buffer_equals_values;
};

SeekStartOutcome buffer_adaptor_write_seek_start_outcome() {
  std::vector<std::uint8_t> buffer{1, 2, 3};
  hexi::buffer_adaptor adaptor(buffer);

  std::array<std::uint8_t, 3> values{4, 5, 6};
  adaptor.write_seek(hexi::buffer_seek::sk_absolute, 0);
  adaptor.write(values.data(), values.size());

  return SeekStartOutcome{
      .buffer_size = buffer.size(),
      .adaptor_size = adaptor.size(),
      .buffer_equals_values = std::ranges::equal(buffer, values),
  };
}

