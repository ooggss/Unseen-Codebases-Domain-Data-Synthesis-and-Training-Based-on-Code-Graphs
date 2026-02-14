
// Function extracted from TEST(dynamic_buffer, reserve_fetch_consistency)

#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <cstddef>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

/**
 * Reserve space, fetch writable buffers, memcpy input bytes into them, then read back.
 *
 * This mirrors the original test logic:
 * - Reserve text_len bytes (which increases chain.size()).
 * - Fetch buffers covering text_len bytes.
 * - Copy the text into the fetched buffers via each buffer's read_ptr() and size().
 * - Read the reserved content back out into an output string (consuming the chain).
 *
 * @param text_bytes Data to write into the reserved/fetched buffers (size determines reserve amount).
 * @return std::pair<std::string, std::size_t>
 *   - Output bytes read back (size equals text_bytes.size())
 *   - Remaining chain size after readback (should be 0)
 */
std::pair<std::string, std::size_t> dynamic_buffer_reserve_fetch_roundtrip(
    const std::vector<char>& text_bytes) {
  hexi::dynamic_buffer<32> chain;
  const std::size_t text_len = text_bytes.size();

  chain.reserve(text_len);

  auto buffers = chain.fetch_buffers(text_len);

  std::size_t offset = 0;
  for (auto& buffer : buffers) {
    std::memcpy(buffer->read_ptr(), text_bytes.data() + offset, buffer->size());
    offset += buffer->size();

    if (offset > text_len || !offset) {
      break;
    }
  }

  std::string output;
  output.resize_and_overwrite(text_len, [&](char* strbuf, std::size_t size) {
    chain.read(strbuf, size);
    return size;
  });

  return {output, chain.size()};
}
