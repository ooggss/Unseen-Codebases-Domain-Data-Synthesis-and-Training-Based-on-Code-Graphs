
// Function extracted from TEST(dynamic_buffer, attach_tail)

#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <cstddef>
#include <cstring>
#include <string>
#include <tuple>
#include <utility>

/**
 * Allocate a buffer node, write text into it, attach it to the chain, then read it back.
 *
 * Mirrors the test's sequence:
 * - Allocate a buffer node from the chain allocator.
 * - Write the provided text into the node.
 * - push_back the node into the chain.
 * - skip the first block (32 bytes) to move the read cursor.
 * - advance_write(written) to reflect produced bytes.
 * - Read back exactly 'written' bytes and compare externally.
 *
 * @param text Input string to write into the allocated buffer node.
 * @return std::tuple<std::size_t, std::string, std::size_t>
 *   - written byte count as returned by buffer->write(...)
 *   - output bytes read back (length equals written)
 *   - remaining chain size after readback (expected 0)
 */
std::tuple<std::size_t, std::string, std::size_t> dynamic_buffer_attach_tail_roundtrip(
    const std::string& text) {
  hexi::dynamic_buffer<32> chain;
  auto buffer = chain.get_allocator().allocate();

  const std::size_t written = buffer->write(text.c_str(), text.length());

  chain.push_back(buffer);
  chain.skip(32);               // skip first block
  chain.advance_write(written); // commit written bytes to chain size

  std::string output;
  output.resize_and_overwrite(written, [&](char* strbuf, std::size_t size) {
    chain.read(strbuf, size);
    return size;
  });

  return {written, output, chain.size()};
}
