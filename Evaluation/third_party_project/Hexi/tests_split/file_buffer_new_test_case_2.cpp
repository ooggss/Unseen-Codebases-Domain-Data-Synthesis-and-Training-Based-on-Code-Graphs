
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>

#include <cstdint>
#include <filesystem>
#include <vector>

// Include function definition (normally via a header)
#include "file_buffer_function_implementation_2.hpp"

namespace file_buffer_test_copy {

TEST(file_buffer, copy) {
  const std::filesystem::path path("data/filebuffer");

  const std::vector<std::uint8_t> observed = copy_read_observed_bytes(path);

  ASSERT_EQ(observed.size(), 4u);
  ASSERT_EQ(observed[0], 47);
  ASSERT_EQ(observed[1], 47);
  ASSERT_EQ(observed[2], 47);
  ASSERT_EQ(observed[3], 45);
}

}  // namespace file_buffer_test_copy
