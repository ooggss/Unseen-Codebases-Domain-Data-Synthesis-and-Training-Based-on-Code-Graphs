
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include "helpers.h"

#include <hexi/endian.h>
#include <hexi/file_buffer.h>

#include <cstdint>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

namespace file_buffer_test_write {

using ByteVec = std::vector<char>;

/**
 * Creates a file, writes a fixed binary payload (with little-endian integer fields),
 * flushes it, then returns the raw bytes of both a reference file and the newly
 * created file for comparison.
 *
 * The written payload layout is:
 *  1) uint8_t  w (native)
 *  2) uint16_t x (written as little-endian)
 *  3) uint32_t y (written as little-endian)
 *  4) uint64_t z (written as little-endian)
 *  5) string bytes including a trailing '\0' terminator.
 *
 * Note: This function deletes any existing file at `path` before writing.
 *
 * @param path Output file path to create/write.
 * @param reference_path Path to an existing reference file to compare against.
 * @param w First integer field to write.
 * @param x 16-bit integer field to write (will be converted to little-endian before writing).
 * @param y 32-bit integer field to write (will be converted to little-endian before writing).
 * @param z 64-bit integer field to write (will be converted to little-endian before writing).
 * @param str String payload to write, including its null terminator.
 * @return Pair of byte vectors: {reference_bytes, created_bytes}.
 *
 * @throws std::runtime_error if reference file does not exist, output file cannot
 *         be opened, or any I/O failure is detected.
 */
std::pair<ByteVec, ByteVec> write_filebuffer_and_read_back(
    const std::filesystem::path& path, const std::filesystem::path& reference_path,
    std::uint8_t w, std::uint16_t x, std::uint32_t y, std::uint64_t z,
    const std::string& str) {
  if (!std::filesystem::exists(reference_path)) {
    throw std::runtime_error("Reference file does not exist: " + reference_path.string());
  }

  // Remove any pre-existing file.
  std::filesystem::remove(path);

  hexi::file_buffer buffer(path);
  if (!buffer) {
    throw std::runtime_error("File open failed: " + path.string());
  }

  hexi::endian::native_to_little_inplace(x);
  hexi::endian::native_to_little_inplace(y);
  hexi::endian::native_to_little_inplace(z);

  buffer.write(w);
  buffer.write(x);
  buffer.write(y);
  buffer.write(z);
  buffer.write(str.data(), str.size() + 1);  // write terminator
  buffer.flush();                            // ensure data has been written

  const auto reference = read_file(reference_path.string().c_str());
  const auto created = read_file(path.string().c_str());
  return {reference, created};
}

}  // namespace file_buffer_test_write
