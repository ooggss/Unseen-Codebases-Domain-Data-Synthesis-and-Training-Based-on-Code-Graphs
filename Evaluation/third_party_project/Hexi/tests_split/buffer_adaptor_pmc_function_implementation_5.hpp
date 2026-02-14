
#include <hexi/pmc/buffer_adaptor.h>
#include <algorithm>
#include <array>
#include <vector>
#include <cstdint>

/**
 * @brief Read all bytes from an adaptor into an output array and return both expected and actual.
 *
 * The function prepares an `expected` byte array {1,2,3}, copies it into a vector buffer,
 * reads all bytes through `buffer_adaptor` into `values`, and returns both arrays
 * so the caller can compare them.
 *
 * @return std::pair<std::array<std::uint8_t, 3>, std::array<std::uint8_t, 3>>
 *   - first: expected bytes
 *   - second: bytes read from adaptor
 */
namespace pmc_split {

inline std::pair<std::array<std::uint8_t, 3>, std::array<std::uint8_t, 3>> buffer_adaptor_read_all_values() {
	std::array<std::uint8_t, 3> expected{1, 2, 3};
	std::vector<std::uint8_t> buffer(expected.begin(), expected.end());
	hexi::pmc::buffer_adaptor adaptor(buffer);

	std::array<std::uint8_t, 3> values{};
	adaptor.read(values.data(), values.size());

	return {expected, values};
}
} // namespace pmc_split
