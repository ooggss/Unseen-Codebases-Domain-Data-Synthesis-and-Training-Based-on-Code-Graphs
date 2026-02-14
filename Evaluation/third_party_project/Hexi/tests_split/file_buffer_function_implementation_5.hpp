
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/file_buffer.h>

#include <cstdint>
#include <filesystem>
#include <stdexcept>

namespace file_buffer_test_interleave {

struct InterleaveResult {
  std::uint8_t u8_out;
  std::uint16_t u16_out;
  std::uint32_t u32_out;
  std::uint64_t u64_out;
  std::uint16_t x_out;
  std::uint16_t y_out;
};

/**
 * Writes and immediately reads back several integer values from a file_buffer,
 * exercising interleaved read/write behavior.
 *
 * The function:
 *  - removes any pre-existing file at `path`
 *  - opens a hexi::file_buffer
 *  - performs 4 sequences of write(value) then read(out) for u8/u16/u32/u64
 *  - writes two uint16 values then reads them back in order
 *
 * @param path File path to create/use for interleaved operations.
 * @param u8_in Input uint8 value to write/read back.
 * @param u16_in Input uint16 value to write/read back.
 * @param u32_in Input uint32 value to write/read back.
 * @param u64_in Input uint64 value to write/read back.
 * @param x_in First uint16 in the final paired write/read.
 * @param y_in Second uint16 in the final paired write/read.
 * @return InterleaveResult containing all values read back from the buffer.
 *
 * @throws std::runtime_error if the file cannot be opened.
 */
InterleaveResult interleaved_write_read(const std::filesystem::path& path,
                                       std::uint8_t u8_in,
                                       std::uint16_t u16_in,
                                       std::uint32_t u32_in,
                                       std::uint64_t u64_in,
                                       std::uint16_t x_in,
                                       std::uint16_t y_in) {
  std::filesystem::remove(path);

  hexi::file_buffer buffer(path);
  if (!buffer) {
    throw std::runtime_error("File open failed: " + path.string());
  }

  InterleaveResult r{};

  buffer.write(u8_in);
  buffer.read(&r.u8_out);

  buffer.write(u16_in);
  buffer.read(&r.u16_out);

  buffer.write(u32_in);
  buffer.read(&r.u32_out);

  buffer.write(u64_in);
  buffer.read(&r.u64_out);

  buffer.write(x_in);
  buffer.write(y_in);
  buffer.read(&r.x_out);
  buffer.read(&r.y_out);

  return r;
}

}  // namespace file_buffer_test_interleave
