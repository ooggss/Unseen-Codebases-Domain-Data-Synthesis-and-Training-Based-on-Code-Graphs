
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include "final_action.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <ranges>
#include <string>
#include <utility>

// Include function definition (normally via a header)
#include "file_buffer_function_implementation_1.hpp"

namespace file_buffer_test_write {

TEST(file_buffer, write) {
  const std::filesystem::path path{"tmp_unittest_file_buffer_write"};
  const std::filesystem::path reference_path{"data/filebuffer"};

  final_action fa([path] { std::filesystem::remove(path); });

  const std::uint8_t w = 47;
  const std::uint16_t x = 49197;
  const std::uint32_t y = 2173709693;
  const std::uint64_t z = 1438110846748337907;
  const std::string str{"The quick brown fox jumped over the lazy dog."};

  const auto [reference, created] =
      write_filebuffer_and_read_back(path, reference_path, w, x, y, z, str);

  ASSERT_TRUE(std::ranges::equal(reference, created));
}

}  // namespace file_buffer_test_write
