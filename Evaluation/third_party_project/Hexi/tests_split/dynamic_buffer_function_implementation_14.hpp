
// Function extracted from TEST(dynamic_buffer, block_count)

#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <cstddef>
#include <cstdint>
#include <vector>

/**
 * Write single bytes into a dynamic_buffer<1> to force new blocks and report block_count over time.
 *
 * Sequence:
 * - Write 1 byte: block_count should be 1.
 * - Write another byte: block_count should be 2.
 * - Write two more bytes: block_count should be 4.
 * - pop_front one block: block_count should be 3.
 *
 * @param value Byte value to write repeatedly.
 * @return std::vector<std::size_t> Block counts observed after each stage: [1,2,4,3].
 */
std::vector<std::size_t> dynamic_buffer_block_count_sequence(std::uint8_t value) {
  hexi::dynamic_buffer<1> chain;
  std::vector<std::size_t> counts;
  counts.reserve(4);

  chain.write(&value, sizeof(value));
  counts.push_back(chain.block_count());

  chain.write(&value, sizeof(value));
  counts.push_back(chain.block_count());

  chain.write(&value, sizeof(value));
  chain.write(&value, sizeof(value));
  counts.push_back(chain.block_count());

  chain.pop_front();
  counts.push_back(chain.block_count());

  return counts;
}
