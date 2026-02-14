
// Function extracted from TEST(dynamic_buffer, block_size)

#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <cstddef>
#include <utility>

/**
 * Construct dynamic_buffers of two template block sizes and return their reported block_size().
 *
 * @return std::pair<std::size_t, std::size_t>
 *   - block_size() for dynamic_buffer<32>
 *   - block_size() for dynamic_buffer<64>
 */
std::pair<std::size_t, std::size_t> dynamic_buffer_report_block_sizes() {
  hexi::dynamic_buffer<32> chain;
  hexi::dynamic_buffer<64> chain2;
  return {chain.block_size(), chain2.block_size()};
}
