
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/file_buffer.h>

#include <cstdint>
#include <filesystem>
#include <stdexcept>
#include <vector>

namespace file_buffer_test_copy {

/**
 * Executes a sequence of copy/read operations on a file_buffer and returns the
 * observed bytes.
 *
 * Operation sequence:
 *  - copy into `in` (does not advance cursor) and record
 *  - copy again and record
 *  - read (advances cursor) and record
 *  - copy again (from new cursor position) and record
 *
 * @param path Path to the file to open.
 * @return Vector of the four observed uint8 values in the order they were observed.
 *
 * @throws std::runtime_error if the file does not exist or cannot be opened.
 */
std::vector<std::uint8_t> copy_read_observed_bytes(const std::filesystem::path& path) {
  if (!std::filesystem::exists(path)) {
    throw std::runtime_error("File does not exist: " + path.string());
  }

  hexi::file_buffer buffer(path);
  if (!buffer) {
    throw std::runtime_error("File open failed: " + path.string());
  }

  std::vector<std::uint8_t> observed;
  observed.reserve(4);

  std::uint8_t in = 0;
  buffer.copy(&in);
  observed.push_back(in);
  buffer.copy(&in);
  observed.push_back(in);
  buffer.read(&in);  // advance to next byte without skip
  observed.push_back(in);
  buffer.copy(&in);
  observed.push_back(in);

  return observed;
}

}  // namespace file_buffer_test_copy
