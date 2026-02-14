
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include "final_action.h"

#include <gtest/gtest.h>

#include <cstdint>
#include <filesystem>

// Include function definition (normally via a header)
#include "file_buffer_function_implementation_5.hpp"

namespace file_buffer_test_interleave {

TEST(file_buffer, read_write_interleave) {
  const std::filesystem::path path{"tmp_unittest_file_buffer_read_write_mix"};
  final_action fa([path] { std::filesystem::remove(path); });

  const std::uint8_t u8_in = 42;
  const std::uint16_t u16_in = 64245;
  const std::uint32_t u32_in = 80144;
  const std::uint64_t u64_in = 1438110846748337907;
  const std::uint16_t x_in = 60925;
  const std::uint16_t y_in = 1352;

  const auto r = interleaved_write_read(path, u8_in, u16_in, u32_in, u64_in, x_in, y_in);

  ASSERT_EQ(r.u8_out, u8_in);
  ASSERT_EQ(r.u16_out, u16_in);
  ASSERT_EQ(r.u32_out, u32_in);
  ASSERT_EQ(r.u64_out, u64_in);
  ASSERT_EQ(r.x_out, x_in);
  ASSERT_EQ(r.y_out, y_in);
}

}  // namespace file_buffer_test_interleave
