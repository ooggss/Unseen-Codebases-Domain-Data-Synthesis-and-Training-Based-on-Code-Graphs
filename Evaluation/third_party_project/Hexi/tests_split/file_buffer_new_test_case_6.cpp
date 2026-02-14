
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>

#include <filesystem>
#include <cstdint>

// Include function definition (normally via a header)
#include "file_buffer_function_implementation_6.hpp"

namespace file_buffer_test_find_first_of {

TEST(file_buffer, find_first_of) {
  const std::filesystem::path path("data/filebuffer");

  const auto r = run_find_first_of_queries(path);

  EXPECT_EQ(r.pos_2f, 0u);
  EXPECT_EQ(r.pos_20, 18u);
  EXPECT_EQ(r.pos_6f, 27u);
  EXPECT_EQ(r.pos_6a, 35u);
  EXPECT_EQ(r.pos_00, 60u);
  EXPECT_EQ(r.pos_ff, hexi::file_buffer::npos);
  ASSERT_TRUE(r.ok) << "Error occurred during seeking";
}

}  // namespace file_buffer_test_find_first_of
