
// Function extracted from TEST(dynamic_buffer, retrieve_tail)

#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <cstddef>
#include <cstring>
#include <string>
#include <utility>

/**
 * Write text to the chain and retrieve the tail buffer node, returning the raw comparison result.
 *
 * @param text Text bytes to write into the chain.
 * @return std::pair<bool, int>
 *   - Whether the returned tail buffer pointer was non-null.
 *   - Result of std::memcmp between text bytes and tail storage (0 means match).
 */
std::pair<bool, int> dynamic_buffer_retrieve_tail_compare(const std::string& text) {
  hexi::dynamic_buffer<32> chain;
  chain.write(text.data(), text.length());

  auto tail = chain.back();
  if (!tail) {
    return {false, 0};
  }

  const int cmp = std::memcmp(text.data(), tail->storage.data(), text.length());
  return {true, cmp};
}
