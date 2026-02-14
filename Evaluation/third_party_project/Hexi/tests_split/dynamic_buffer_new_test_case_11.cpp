
#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <gtest/gtest.h>
#include <array>
#include <cstdint>
#include <cstring>
#include <tuple>
#include <vector>

#include "dynamic_buffer_function_implementation_11.hpp"

TEST(dynamic_buffer, write_seek) {
  const std::array<std::uint8_t, 6> data{0x00, 0x01, 0x00, 0x00, 0x04, 0x05};
  const std::array<std::uint8_t, 2> seek_data{0x02, 0x03};
  const std::array<std::uint8_t, 4> expected_data{0x00, 0x01, 0x02, 0x03};

  const std::array<std::uint8_t, 8> final_data{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
  const std::array<std::uint8_t, 2> new_data{0x06, 0x07};

  const auto [size_after_rewrite, out1, size_after_append, out2] =
      dynamic_buffer_write_seek_patterns(
          std::vector<std::uint8_t>(data.begin(), data.end()),
          /*backward_amount=*/4,
          std::vector<std::uint8_t>(seek_data.begin(), seek_data.end()),
          /*forward_amount=*/2,
          std::vector<std::uint8_t>(new_data.begin(), new_data.end()));

  ASSERT_EQ(size_after_rewrite, 4u) << "Chain size is incorrect";
  ASSERT_EQ(0, std::memcmp(out1.data(), expected_data.data(), expected_data.size()))
      << "Buffer contains incorrect data pattern";

  ASSERT_EQ(size_after_append, final_data.size()) << "Chain size is incorrect";
  ASSERT_EQ(0, std::memcmp(out2.data(), final_data.data(), final_data.size()))
      << "Buffer contains incorrect data pattern";
}
