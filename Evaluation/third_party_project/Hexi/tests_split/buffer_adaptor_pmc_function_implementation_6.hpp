
#include <hexi/pmc/buffer_adaptor.h>
#include <vector>
#include <cstdint>
#include <tuple>

/**
 * @brief Skip one byte, then read one byte, returning remaining size and the read value.
 *
 * The function uses a buffer {1,2,3}, skips 1 byte, reads 1 byte, and returns:
 * - adaptor size after operations (expected 1)
 * - the read value (expected to be the second element, i.e., 2)
 * - the expected value taken from the original buffer at index 1
 *
 * @return std::tuple<std::size_t, std::uint8_t, std::uint8_t>
 *   - 0: adaptor.size() after skip+read
 *   - 1: read value
 *   - 2: original buffer[1] for comparison
 */
namespace pmc_split {

inline std::tuple<std::size_t, std::uint8_t, std::uint8_t> buffer_adaptor_single_skip_read() {
	std::vector<std::uint8_t> buffer{1, 2, 3};
	hexi::pmc::buffer_adaptor adaptor(buffer);

	std::uint8_t value = 0;
	adaptor.skip(1);
	adaptor.read(&value, 1);

	return {adaptor.size(), value, buffer[1]};
}
} // namespace pmc_split
