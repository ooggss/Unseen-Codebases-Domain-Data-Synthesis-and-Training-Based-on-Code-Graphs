
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/file_buffer.h>

#include <cstdint>
#include <filesystem>
#include <stdexcept>

namespace file_buffer_test_skip {

struct SkipResult {
  std::uint8_t first_u8;
  std::uint8_t second_u8;
  std::uint32_t u32_after_skips;
  bool ok;
};

/**
 * Opens a file_buffer and performs a fixed sequence of reads and skips, returning
 * the values read and whether the buffer ended in a good state.
 *
 * Sequence:
 *  - read uint8 -> first_u8
 *  - skip 1 byte
 *  - read uint8 -> second_u8
 *  - skip 4 bytes
 *  - read uint32 -> u32_after_skips
 *  - ok is set to buffer's truthiness after operations
 *
 * @param path Path to the file to open.
 * @return SkipResult containing read values and final buffer status.
 *
 * @throws std::runtime_error if the file does not exist or cannot be opened.
 */
SkipResult read_with_skips(const std::filesystem::path& path) {
  if (!std::filesystem::exists(path)) {
    throw std::runtime_error("File does not exist: " + path.string());
  }

  hexi::file_buffer buffer(path);
  if (!buffer) {
    throw std::runtime_error("File open failed: " + path.string());
  }

  SkipResult r{};
  r.ok = false;

  buffer.read(&r.first_u8);
  buffer.skip(1);
  buffer.read(&r.second_u8);

  buffer.skip(4);

  buffer.read(&r.u32_after_skips);

  r.ok = static_cast<bool>(buffer);
  return r;
}

}  // namespace file_buffer_test_skip
