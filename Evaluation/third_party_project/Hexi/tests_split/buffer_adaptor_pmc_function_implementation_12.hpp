
#include <hexi/pmc/buffer_adaptor.h>
#include <array>
#include <ranges>
#include <vector>
#include <cstdint>
#include <tuple>

/**
 * @brief Seek to the start of the buffer and overwrite with new bytes, returning sizes and equality.
 *
 * The function:
 * 1) Starts with buffer {1,2,3}
 * 2) Seeks to absolute position 0
 * 3) Writes {4,5,6}, resulting buffer {4,5,6}
 *
 * @return std::tuple<std::size_t, std::size_t, bool>
 *   - 0: buffer.size() after overwrite (expected 3)
 *   - 1: adaptor.size() after overwrite (expected equal to buffer.size())
 *   - 2: whether buffer equals written values
 */
namespace pmc_split {

inline std::tuple<std::size_t, std::size_t, bool> buffer_adaptor_write_seek_start_result() {
	std::vector<std::uint8_t> buffer{1, 2, 3};
	hexi::pmc::buffer_adaptor adaptor(buffer);

	std::array<std::uint8_t, 3> values{4, 5, 6};
	adaptor.write_seek(hexi::buffer_seek::sk_absolute, 0);
	adaptor.write(values.data(), values.size());

	const bool equals = std::ranges::equal(buffer, values);
	return {buffer.size(), adaptor.size(), equals};
}
} // namespace pmc_split
