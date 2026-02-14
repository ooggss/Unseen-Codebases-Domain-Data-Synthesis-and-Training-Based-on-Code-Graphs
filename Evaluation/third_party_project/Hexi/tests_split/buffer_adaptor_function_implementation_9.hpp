

// Split from original test: buffer_adaptor.write_append

#include <hexi/buffer_adaptor.h>
#include <vector>
#include <array>
#include <ranges>
#include <cstdint>

/**
 * @brief Append bytes to an existing vector through buffer_adaptor and return final state for checks.
 *
 * This function models the functional portion of the original test case:
 * - Starts with vector {1,2,3}
 * - Writes {4,5,6} via adaptor.write
 * - Builds expected {1,2,3,4,5,6}
 * - Returns final buffer size, adaptor size, and whether buffer equals expected
 *
 * @return struct AppendOutcome
 * Aggregated results used by the test assertions.
 */
struct AppendOutcome {
  std::size_t buffer_size;
  std::size_t adaptor_size;
  bool buffer_equals_expected;
};

AppendOutcome buffer_adaptor_write_append_outcome() {
  std::vector<std::uint8_t> buffer{1, 2, 3};
  hexi::buffer_adaptor adaptor(buffer);

  std::array<std::uint8_t, 3> values{4, 5, 6};
  adaptor.write(values.data(), values.size());

  std::array<std::uint8_t, 6> expected{1, 2, 3, 4, 5, 6};
  return AppendOutcome{
      .buffer_size = buffer.size(),
      .adaptor_size = adaptor.size(),
      .buffer_equals_expected = std::ranges::equal(expected, buffer),
  };
}

