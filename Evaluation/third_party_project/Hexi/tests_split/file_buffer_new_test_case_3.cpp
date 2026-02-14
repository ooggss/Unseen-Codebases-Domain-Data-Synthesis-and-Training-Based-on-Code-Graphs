
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>

#include <filesystem>

// Include function definition (normally via a header)
#include "file_buffer_function_implementation_3.hpp"

namespace file_buffer_test_skip {

TEST(file_buffer, skip) {
  const std::filesystem::path path("data/filebuffer");

  const auto r = read_with_skips(path);

  ASSERT_EQ(r.first_u8, 47);
  ASSERT_EQ(r.second_u8, 192);
  ASSERT_EQ(r.u32_after_skips, 403842803u);
  ASSERT_TRUE(r.ok) << "Read failure";
}

}  // namespace file_buffer_test_skip
