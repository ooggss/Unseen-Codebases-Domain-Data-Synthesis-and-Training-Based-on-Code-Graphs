
#include <hexi/pmc/buffer_adaptor.h>
#include <vector>
#include <cstdint>
#include <tuple>

/**
 * @brief Skip multiple bytes then read the last byte, returning empty state and the read value.
 *
 * The function constructs a buffer {1,2,3,4,5,6} and a `buffer_adaptor` with buffer reuse
 * optimization disabled (`false` template parameter as in the original test).
 * It skips 5 bytes and reads 1 byte. It then returns:
 * - whether the adaptor is empty after operations (expected true)
 * - the read value (expected buffer[5] == 6)
 * - the expected value from the original buffer at index 5
 *
 * @return std::tuple<bool, std::uint8_t, std::uint8_t>
 *   - 0: adaptor.empty() after skip+read
 *   - 1: read value
 *   - 2: original buffer[5] for comparison
 */
namespace pmc_split {

inline std::tuple<bool, std::uint8_t, std::uint8_t> buffer_adaptor_multiskip_read() {
	std::vector<std::uint8_t> buffer{1, 2, 3, 4, 5, 6};
	hexi::pmc::buffer_adaptor<decltype(buffer), false> adaptor(buffer);

	std::uint8_t value = 0;
	adaptor.skip(5);
	adaptor.read(&value, 1);

	return {adaptor.empty(), value, buffer[5]};
}
} // namespace pmc_split
