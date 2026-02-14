
// Function extracted from TEST(dynamic_buffer, copy_chain)

#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <cstddef>
#include <tuple>

/**
 * Copy-assign one dynamic_buffer into another and observe independence of storage.
 *
 * Sequence:
 * - Write two ints into chain.
 * - Copy-assign chain2 = chain.
 * - Read one int from chain (consumes from chain only).
 * - Clear chain (chain2 must remain intact).
 * - Read one int from chain2 (should match original value).
 *
 * @param value Integer to write twice.
 * @return std::tuple<std::size_t, std::size_t, std::size_t, std::size_t, std::size_t, int>
 *   - chain size after two writes
 *   - chain2 size before copy assignment
 *   - chain size after copy assignment
 *   - chain2 size after copy assignment
 *   - chain size after reading one int from chain
 *   - value read from chain2 after chain was cleared
 */
std::tuple<std::size_t, std::size_t, std::size_t, std::size_t, std::size_t, int>
dynamic_buffer_copy_chain_independence(int value) {
  hexi::dynamic_buffer<sizeof(int)> chain, chain2;

  chain.write(&value, sizeof(int));
  chain.write(&value, sizeof(int));

  const std::size_t size_after_writes = chain.size();
  const std::size_t chain2_before = chain2.size();

  chain2 = chain;

  const std::size_t chain_after_copy = chain.size();
  const std::size_t chain2_after_copy = chain2.size();

  int tmp = 0;
  chain.read(&tmp, sizeof(int));
  const std::size_t chain_after_read = chain.size();

  chain.clear();

  int out_from_chain2 = 0;
  chain2.read(&out_from_chain2, sizeof(int));

  return {size_after_writes, chain2_before, chain_after_copy, chain2_after_copy,
          chain_after_read, out_from_chain2};
}
