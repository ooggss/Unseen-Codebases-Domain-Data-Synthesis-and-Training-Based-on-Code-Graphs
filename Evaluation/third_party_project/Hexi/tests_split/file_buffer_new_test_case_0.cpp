
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>

#include <filesystem>
#include <string_view>

// Include function definition (normally via a header)
#include "file_buffer_function_implementation_0.hpp"

namespace file_buffer_test_read {

TEST(file_buffer, read) {
  const std::filesystem::path path("data/filebuffer");
  const std::string_view strcmp{"The quick brown fox jumped over the lazy dog."};

  const auto r = read_filebuffer_payload(path, strcmp);

  ASSERT_EQ(r.w, 47) << "Wrong uint8 value";
  ASSERT_EQ(r.x, 49197) << "Wrong uint16 value";
  ASSERT_EQ(r.y, 2173709693) << "Wrong uint32 value";
  ASSERT_EQ(r.z, 1438110846748337907) << "Wrong uint64 value";
  ASSERT_EQ(r.str_out, strcmp);
}

}  // namespace file_buffer_test_read
