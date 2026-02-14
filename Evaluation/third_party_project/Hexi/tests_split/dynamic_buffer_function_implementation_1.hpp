
// Function extracted from TEST(dynamic_buffer, read_write_consistency)

#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <cstring>
#include <string>
#include <tuple>
#include <vector>

/**
 * Write a text blob and an integer to a dynamic_buffer and then read them back.
 *
 * The function:
 * - Writes the full input text (including its terminating '\0' if present in the provided bytes)
 *   into the buffer.
 * - Writes the integer as raw bytes.
 * - Reads back the same number of bytes for text and the integer.
 *
 * @param text_bytes Byte sequence to write as "text" (caller controls whether it includes '\0').
 * @param num Integer value to write after the text.
 * @return std::tuple<int, std::string, std::size_t>
 *   - The integer read back
 *   - The text read back (as a std::string containing exactly text_bytes.size() bytes)
 *   - Remaining size in the chain after reads (should be 0 for a full readback)
 */
std::tuple<int, std::string, std::size_t> dynamic_buffer_read_write_roundtrip(
    const std::vector<char>& text_bytes,
    int num) {
  hexi::dynamic_buffer<32> chain;

  chain.write(text_bytes.data(), text_bytes.size());
  chain.write(&num, sizeof(int));

  std::string text_out(text_bytes.size(), '\0');
  int num_out = 0;

  chain.read(text_out.data(), text_bytes.size());
  chain.read(&num_out, sizeof(int));

  return {num_out, text_out, chain.size()};
}
