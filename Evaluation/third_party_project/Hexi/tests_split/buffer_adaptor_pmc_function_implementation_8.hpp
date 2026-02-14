
#include <hexi/pmc/buffer_adaptor.h>
#include <algorithm>
#include <array>
#include <ranges>
#include <vector>
#include <cstdint>
#include <tuple>

/**
 * @brief Write an array to an empty adaptor, then write a single extra byte; return observed sizes and equality.
 *
 * The function:
 * 1) Writes {1,2,3,4,5,6} into an initially empty vector via `buffer_adaptor::write`.
 * 2) Captures adaptor.size(), buffer.size(), and whether buffer contents equal the written values.
 * 3) Writes one additional byte ('\0') and captures adaptor.size() afterwards.
 *
 * @return std::tuple<std::size_t, std::size_t, bool, std::size_t>
 *   - 0: size after writing the array (adaptor.size())
 *   - 1: underlying buffer size after writing the array (buffer.size())
 *   - 2: whether buffer equals the written array
 *   - 3: size after writing an additional single byte
 */
namespace pmc_split {

inline std::tuple<std::size_t, std::size_t, bool, std::size_t> buffer_adaptor_write_and_append_one() {
	std::vector<std::uint8_t> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);

	std::array<std::uint8_t, 6> values{1, 2, 3, 4, 5, 6};
	adaptor.write(values.data(), values.size());

	const std::size_t size_after_array = adaptor.size();
	const std::size_t buffer_size_after_array = buffer.size();
	const bool equals = std::ranges::equal(values, buffer);

	const auto size_before_single = adaptor.size();
	adaptor.write('\0');
	const std::size_t size_after_single = adaptor.size();

	(void)size_before_single; // kept conceptually; size_after_single should be size_after_array + 1
	return {size_after_array, buffer_size_after_array, equals, size_after_single};
}
} // namespace pmc_split
