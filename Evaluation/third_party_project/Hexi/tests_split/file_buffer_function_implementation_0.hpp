
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/endian.h>
#include <hexi/file_buffer.h>

#include <cstdint>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

namespace file_buffer_test_read {

struct ReadResult {
  std::uint8_t w;
  std::uint16_t x;
  std::uint32_t y;
  std::uint64_t z;
  std::string str_out;
};

/**
 * Reads a binary test file and decodes a fixed layout payload.
 *
 * The file is expected to contain, in order:
 *  1) uint8_t  w
 *  2) uint16_t x (little-endian)
 *  3) uint32_t y (little-endian)
 *  4) uint64_t z (little-endian)
 *  5) A byte sequence of length strcmp.size() (no terminator required),
 *     which is read into a std::string and returned as str_out.
 *
 * After reading, integer values x/y/z are converted from little-endian to native.
 *
 * @param path Path to the file to read.
 * @param strcmp Reference string whose length determines how many bytes are read
 *               for the trailing string payload.
 * @return ReadResult containing decoded integers and the read string.
 *
 * @throws std::runtime_error if the file does not exist, cannot be opened, or
 *         a read error occurs.
 */
ReadResult read_filebuffer_payload(const std::filesystem::path& path,
                                  std::string_view strcmp) {
  if (!std::filesystem::exists(path)) {
    throw std::runtime_error("File does not exist: " + path.string());
  }

  hexi::file_buffer buffer(path);
  if (!buffer) {
    throw std::runtime_error("File open failed: " + path.string());
  }

  ReadResult r{};
  r.str_out.resize(strcmp.size());

  buffer.read(&r.w);
  buffer.read(&r.x);
  buffer.read(&r.y);
  buffer.read(&r.z);
  buffer.read(r.str_out.data(), r.str_out.size());

  if (!buffer) {
    throw std::runtime_error("File read error occurred: " + path.string());
  }

  hexi::endian::little_to_native_inplace(r.x);
  hexi::endian::little_to_native_inplace(r.y);
  hexi::endian::little_to_native_inplace(r.z);

  return r;
}

}  // namespace file_buffer_test_read
