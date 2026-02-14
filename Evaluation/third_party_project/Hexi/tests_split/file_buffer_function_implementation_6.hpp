
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/file_buffer.h>

#include <cstdint>
#include <filesystem>
#include <stdexcept>

namespace file_buffer_test_find_first_of {

struct FindFirstOfResult {
  std::uint64_t pos_2f;
  std::uint64_t pos_20;
  std::uint64_t pos_6f;
  std::uint64_t pos_6a;
  std::uint64_t pos_00;
  std::uint64_t pos_ff;
  bool ok;
};

/**
 * Opens a file_buffer and performs several find_first_of() queries, returning
 * the resulting positions and final buffer state.
 *
 * The function searches for the following bytes: 0x2f, 0x20, 0x6f, 0x6a, 0x00, 0xff.
 *
 * @param path Path to the file to open.
 * @return FindFirstOfResult containing positions (or hexi::file_buffer::npos)
 *         for each query and a boolean indicating whether the buffer remained valid.
 *
 * @throws std::runtime_error if the file does not exist or cannot be opened.
 */
FindFirstOfResult run_find_first_of_queries(const std::filesystem::path& path) {
  if (!std::filesystem::exists(path)) {
    throw std::runtime_error("File does not exist: " + path.string());
  }

  hexi::file_buffer buffer(path);
  if (!buffer) {
    throw std::runtime_error("File open failed: " + path.string());
  }

  FindFirstOfResult r{};
  r.pos_2f = buffer.find_first_of(0x2f);
  r.pos_20 = buffer.find_first_of(0x20);
  r.pos_6f = buffer.find_first_of(0x6f);
  r.pos_6a = buffer.find_first_of(0x6a);
  r.pos_00 = buffer.find_first_of(0x00);
  r.pos_ff = buffer.find_first_of(0xff);
  r.ok = static_cast<bool>(buffer);

  return r;
}

}  // namespace file_buffer_test_find_first_of
