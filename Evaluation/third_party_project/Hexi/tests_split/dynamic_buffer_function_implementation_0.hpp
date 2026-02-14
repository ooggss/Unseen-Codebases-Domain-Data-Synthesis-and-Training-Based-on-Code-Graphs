
// Function extracted from TEST(dynamic_buffer, size)

#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <cstddef>
#include <cstring>
#include <utility>
#include <vector>

/**
 * Execute a sequence of dynamic_buffer operations that exercise size tracking.
 *
 * This function performs the same operational steps as the original test:
 * - Create an empty buffer chain.
 * - Reserve 50 bytes.
 * - Read 20 bytes (consuming from the readable region).
 * - Skip 10 bytes.
 * - Write 20 bytes.
 * - Clear the buffer.
 *
 * The function returns the observed sizes after each step so callers can assert
 * correct size accounting.
 *
 * @param reserve_amount Number of bytes to reserve into the chain.
 * @param read_amount Number of bytes to read from the chain into a temporary buffer.
 * @param skip_amount Number of bytes to skip from the chain.
 * @param write_amount Number of bytes to write into the chain from a temporary buffer.
 * @return std::vector<std::size_t> Sizes observed in order:
 *   [0] initial size,
 *   [1] after reserve,
 *   [2] after read,
 *   [3] after skip,
 *   [4] after write,
 *   [5] after clear.
 */
std::vector<std::size_t> dynamic_buffer_size_sequence(std::size_t reserve_amount,
                                                      std::size_t read_amount,
                                                      std::size_t skip_amount,
                                                      std::size_t write_amount) {
  hexi::dynamic_buffer<32> chain;

  std::vector<std::size_t> sizes;
  sizes.reserve(6);

  sizes.push_back(chain.size());

  chain.reserve(reserve_amount);
  sizes.push_back(chain.size());

  // Use a local scratch buffer for read/write.
  // The original test used char buffer[20]; and read sizeof(buffer).
  std::vector<char> buffer(std::max(read_amount, write_amount), 0);

  chain.read(buffer.data(), read_amount);
  sizes.push_back(chain.size());

  chain.skip(skip_amount);
  sizes.push_back(chain.size());

  chain.write(buffer.data(), write_amount);
  sizes.push_back(chain.size());

  chain.clear();
  sizes.push_back(chain.size());

  return sizes;
}
