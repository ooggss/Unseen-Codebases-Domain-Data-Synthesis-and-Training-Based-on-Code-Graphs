

// Split from original test: buffer_adaptor.subscript

#include <hexi/buffer_adaptor.h>
#include <array>
#include <cstdint>

/**
 * @brief Validate buffer_adaptor operator[] reflects and mutates underlying storage.
 *
 * This function models the functional portion of the original test case:
 * - Creates buffer {1,2,3} and adaptor
 * - Reads adaptor[0..2]
 * - Mutates buffer[0] and observes adaptor[0]
 * - Mutates adaptor[0] and observes both adaptor[0] and buffer[0]
 *
 * @return struct SubscriptOutcome
 * Aggregated observations used by the test assertions.
 */
struct SubscriptOutcome {
  std::uint8_t initial0;
  std::uint8_t initial1;
  std::uint8_t initial2;
  std::uint8_t after_buffer_mutation0;
  std::uint8_t after_adaptor_mutation0;
  std::uint8_t final_buffer0;
};

SubscriptOutcome buffer_adaptor_subscript_outcome() {
  std::array<std::uint8_t, 3> buffer{1, 2, 3};
  hexi::buffer_adaptor adaptor(buffer);

  const auto i0 = adaptor[0];
  const auto i1 = adaptor[1];
  const auto i2 = adaptor[2];

  buffer[0] = 4;
  const auto after_buf = adaptor[0];

  adaptor[0] = 5;
  const auto after_adaptor = adaptor[0];
  const auto final_buf0 = buffer[0];

  return SubscriptOutcome{
      .initial0 = i0,
      .initial1 = i1,
      .initial2 = i2,
      .after_buffer_mutation0 = after_buf,
      .after_adaptor_mutation0 = after_adaptor,
      .final_buffer0 = final_buf0,
  };
}

