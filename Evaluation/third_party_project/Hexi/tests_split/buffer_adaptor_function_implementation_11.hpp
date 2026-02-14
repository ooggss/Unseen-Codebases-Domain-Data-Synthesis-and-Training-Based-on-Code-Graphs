

// Split from original test: buffer_adaptor.write_seek_back

#include <hexi/buffer_adaptor.h>
#include <vector>
#include <array>
#include <ranges>
#include <cstdint>

/**
 * @brief Seek backwards in the write position then overwrite/append data; return final state.
 *
 * This function models the functional portion of the original test case:
 * - Starts with buffer {1,2,3}
 * - Calls adaptor.write_seek(sk_backward, 2) to move write position backward
 * - Writes {4,5,6}
 * - Expects resulting buffer {1,4,5,6}
 *
 * @return struct SeekBackOutcome
 * Aggregated results used by the test assertions.
 */
struct SeekBackOutcome {
  std::size_t buffer_size;
  std::size_t adaptor_size;
  bool buffer_equals_expected;
};

SeekBackOutcome buffer_adaptor_write_seek_back_outcome() {
  std::vector<std::uint8_t> buffer{1, 2, 3};
  hexi::buffer_adaptor adaptor(buffer);

  std::array<std::uint8_t, 3> values{4, 5, 6};
  adaptor.write_seek(hexi::buffer_seek::sk_backward, 2);
  adaptor.write(values.data(), values.size());

  std::array<std::uint8_t, 4> expected{1, 4, 5, 6};
  return SeekBackOutcome{
      .buffer_size = buffer.size(),
      .adaptor_size = adaptor.size(),
      .buffer_equals_expected = std::ranges::equal(expected, buffer),
  };
}

