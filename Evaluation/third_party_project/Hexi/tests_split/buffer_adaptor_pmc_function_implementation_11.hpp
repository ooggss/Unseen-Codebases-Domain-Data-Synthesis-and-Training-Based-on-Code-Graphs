
#include <hexi/pmc/buffer_adaptor.h>
#include <algorithm>
#include <array>
#include <ranges>
#include <vector>
#include <cstdint>
#include <tuple>

/**
 * @brief Seek backward in the write position, overwrite with new bytes, and report resulting buffer state.
 *
 * The function:
 * 1) Starts with buffer {1,2,3}
 * 2) Seeks backward by 2 bytes from the current write position
 * 3) Writes {4,5,6}, effectively overwriting from position 1, resulting in {1,4,5,6}
 *
 * @return std::tuple<std::size_t, std::size_t, bool>
 *   - 0: buffer.size() after operation (expected 4)
 *   - 1: adaptor.size() after operation (expected equal to buffer.size())
 *   - 2: whether buffer equals expected {1,4,5,6}
 */
namespace pmc_split {

inline std::tuple<std::size_t, std::size_t, bool> buffer_adaptor_write_seek_back_result() {
	std::vector<std::uint8_t> buffer{1, 2, 3};
	hexi::pmc::buffer_adaptor adaptor(buffer);

	std::array<std::uint8_t, 3> values{4, 5, 6};
	adaptor.write_seek(hexi::buffer_seek::sk_backward, 2);
	adaptor.write(values.data(), values.size());

	std::array<std::uint8_t, 4> expected{1, 4, 5, 6};
	const bool equals = std::ranges::equal(expected, buffer);

	return {buffer.size(), adaptor.size(), equals};
}
} // namespace pmc_split
