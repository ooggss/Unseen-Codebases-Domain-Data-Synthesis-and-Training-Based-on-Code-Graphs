
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>

#include <filesystem>
#include <cstdint>

// Include function definition (normally via a header)
#include "file_buffer_function_implementation_4.hpp"

namespace file_buffer_test_initial_size {

TEST(file_buffer, initial_size) {
  const std::filesystem::path path("data/filebuffer");

  const std::uint64_t sz = get_initial_filebuffer_size(path);

  ASSERT_EQ(sz, 61u) << "Wrong size";
}

}  // namespace file_buffer_test_initial_size
