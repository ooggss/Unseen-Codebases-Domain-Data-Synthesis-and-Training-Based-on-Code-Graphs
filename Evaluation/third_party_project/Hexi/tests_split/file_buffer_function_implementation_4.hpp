
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/file_buffer.h>

#include <cstdint>
#include <filesystem>
#include <stdexcept>

namespace file_buffer_test_initial_size {

/**
 * Opens a file_buffer for an existing file and returns its initial size.
 *
 * @param path Path to the existing file.
 * @return Size (in bytes) reported by hexi::file_buffer::size() immediately after opening.
 *
 * @throws std::runtime_error if the file does not exist or cannot be opened.
 */
std::uint64_t get_initial_filebuffer_size(const std::filesystem::path& path) {
  if (!std::filesystem::exists(path)) {
    throw std::runtime_error("File does not exist: " + path.string());
  }

  hexi::file_buffer buffer(path);
  if (!buffer) {
    throw std::runtime_error("File open failed: " + path.string());
  }

  return buffer.size();
}

}  // namespace file_buffer_test_initial_size
