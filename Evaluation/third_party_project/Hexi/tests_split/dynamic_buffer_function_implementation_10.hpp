
// Function extracted from TEST(dynamic_buffer, move_chain)

#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <cstddef>
#include <tuple>
#include <utility>

/**
 * Move-assign one dynamic_buffer into another and read back the written integer.
 *
 * @param value Integer to write before moving.
 * @return std::tuple<std::size_t, std::size_t, std::size_t, int>
 *   - size of source after write
 *   - size of destination before move
 *   - size of destination after move
 *   - value read back from destination
 */
std::tuple<std::size_t, std::size_t, std::size_t, int> dynamic_buffer_move_chain_roundtrip(
    int value) {
  hexi::dynamic_buffer<32> chain, chain2;

  chain.write(&value, sizeof(int));
  const std::size_t source_after_write = chain.size();
  const std::size_t dest_before = chain2.size();

  chain2 = std::move(chain);
  const std::size_t dest_after = chain2.size();

  int out = 0;
  chain2.read(&out, sizeof(int));

  return {source_after_write, dest_before, dest_after, out};
}
