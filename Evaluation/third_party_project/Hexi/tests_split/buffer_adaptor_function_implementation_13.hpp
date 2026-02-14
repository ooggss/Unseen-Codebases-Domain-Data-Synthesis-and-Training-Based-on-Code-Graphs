

// Split from original test: buffer_adaptor.read_ptr

#include <hexi/buffer_adaptor.h>
#include <array>
#include <cstdint>
#include <array>

/**
 * @brief Observe the value pointed to by read_ptr() as the read position advances.
 *
 * This function models the functional portion of the original test case:
 * - Creates buffer {1,2,3}
 * - Calls read_ptr(), dereferences it, then skip(1), repeats
 * - Returns the three observed dereferenced values
 *
 * @return std::array<std::uint8_t, 3>
 * The values observed at each read_ptr() call (expected {1,2,3}).
 */
inline std::array<std::uint8_t, 3> buffer_adaptor_read_ptr_sequence() {
  std::array<std::uint8_t, 3> buffer{1, 2, 3};
  hexi::buffer_adaptor adaptor(buffer);

  std::array<std::uint8_t, 3> observed{};

  auto ptr = adaptor.read_ptr();
  observed[0] = *ptr;

  adaptor.skip(1);
  ptr = adaptor.read_ptr();
  observed[1] = *ptr;

  adaptor.skip(1);
  ptr = adaptor.read_ptr();
  observed[2] = *ptr;

  return observed;
}

