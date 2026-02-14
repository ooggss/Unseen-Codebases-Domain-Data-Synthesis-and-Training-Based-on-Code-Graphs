
// Function extracted from TEST(dynamic_buffer, write_seek)

#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <tuple>
#include <vector>

/**
 * Perform a write/seek/rewrite sequence and validate by returning produced byte patterns.
 *
 * Steps:
 * 1) Write initial data bytes.
 * 2) Seek write cursor backward by 4 bytes and overwrite 2 bytes.
 * 3) Copy out current chain bytes (should be 4 bytes total with a specific pattern).
 * 4) Seek write cursor forward by 2 bytes and write 2 new bytes.
 * 5) Read out final chain bytes (should be 8 bytes total with a specific pattern).
 *
 * @param initial_data The initial bytes to write.
 * @param backward_amount How far to seek backward before overwriting.
 * @param overwrite_data The bytes to overwrite after seeking backward.
 * @param forward_amount How far to seek forward after the first validation.
 * @param append_data The bytes to append at the end.
 * @return std::tuple<std::size_t, std::vector<std::uint8_t>, std::size_t, std::vector<std::uint8_t>>
 *   - size after first rewrite (expected 4)
 *   - bytes copied after first rewrite (expected pattern)
 *   - size after final append (expected 8)
 *   - bytes read after final append (expected pattern)
 */
std::tuple<std::size_t, std::vector<std::uint8_t>, std::size_t, std::vector<std::uint8_t>>
dynamic_buffer_write_seek_patterns(const std::vector<std::uint8_t>& initial_data,
                                  std::size_t backward_amount,
                                  const std::vector<std::uint8_t>& overwrite_data,
                                  std::size_t forward_amount,
                                  const std::vector<std::uint8_t>& append_data) {
  hexi::dynamic_buffer<1> chain; // force multiple nodes

  chain.write(initial_data.data(), initial_data.size());
  chain.write_seek(hexi::buffer_seek::sk_backward, backward_amount);
  chain.write(overwrite_data.data(), overwrite_data.size());

  const std::size_t size_after_rewrite = chain.size();
  std::vector<std::uint8_t> out1(chain.size());
  chain.copy(out1.data(), out1.size());

  chain.write_seek(hexi::buffer_seek::sk_forward, forward_amount);
  // chain.size() should now reflect original write cursor position.
  chain.write(append_data.data(), append_data.size());

  const std::size_t size_after_append = chain.size();
  std::vector<std::uint8_t> out2(chain.size());
  chain.read(out2.data(), out2.size());

  return {size_after_rewrite, out1, size_after_append, out2};
}
