
// Function extracted from TEST(dynamic_buffer, pop_front_push_back)

#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <cstddef>
#include <string>
#include <tuple>

/**
 * Push a pre-written buffer node into the chain then pop it from the front.
 *
 * @param text Text to write into an allocated buffer node before attaching.
 * @return std::tuple<std::size_t, std::size_t, std::size_t>
 *   - size before push_back (expected 0)
 *   - size after push_back (expected written)
 *   - size after pop_front (expected 0)
 */
std::tuple<std::size_t, std::size_t, std::size_t> dynamic_buffer_push_back_then_pop_front(
    const std::string& text) {
  hexi::dynamic_buffer<128> chain;  // Use larger blocks to fit the full text
  auto buffer = chain.get_allocator().allocate();

  const std::size_t written = buffer->write(text.c_str(), text.length());

  const std::size_t before = chain.size();
  chain.push_back(buffer);
  const std::size_t after_push = chain.size();
  chain.pop_front();
  const std::size_t after_pop = chain.size();

  // The test asserts after_push == written; we return sizes only.
  (void)written;
  return {before, after_push, after_pop};
}
