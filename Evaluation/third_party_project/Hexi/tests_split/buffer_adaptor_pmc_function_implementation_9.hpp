
#include <hexi/pmc/buffer_adaptor.h>
#include <array>
#include <ranges>
#include <vector>
#include <cstdint>
#include <tuple>

/**
 * @brief Append data to an existing buffer via adaptor and return final sizes and content match.
 *
 * The function starts with buffer {1,2,3}, writes {4,5,6} using the adaptor, and returns:
 * - final buffer size
 * - final adaptor size
 * - whether buffer equals expected {1,2,3,4,5,6}
 *
 * @return std::tuple<std::size_t, std::size_t, bool>
 *   - 0: buffer.size() after append
 *   - 1: adaptor.size() after append
 *   - 2: content equality with expected
 */
namespace pmc_split {

inline std::tuple<std::size_t, std::size_t, bool> buffer_adaptor_write_append_result() {
	std::vector<std::uint8_t> buffer{1, 2, 3};
	hexi::pmc::buffer_adaptor adaptor(buffer);

	std::array<std::uint8_t, 3> values{4, 5, 6};
	adaptor.write(values.data(), values.size());

	std::array<std::uint8_t, 6> expected{1, 2, 3, 4, 5, 6};
	const bool equals = std::ranges::equal(expected, buffer);

	return {buffer.size(), adaptor.size(), equals};
}
} // namespace pmc_split
