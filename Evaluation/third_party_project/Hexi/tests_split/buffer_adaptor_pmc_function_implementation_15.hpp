
#include <hexi/pmc/buffer_adaptor.h>
#include <string_view>
#include <vector>
#include <cstddef>
#include <tuple>

using namespace std::literals;

/**
 * @brief Write a string into a char buffer adaptor and find positions of certain bytes.
 *
 * The function writes "The quick brown fox jumped over the lazy dog" (not null-terminated)
 * into a `std::vector<char>` via `buffer_adaptor`, then queries `find_first_of` for:
 * - '\0' (expected npos because direct write does not append terminator)
 * - 'g' (expected 43)
 * - 'T' (expected 0)
 * - 't' (expected 32)
 *
 * @return std::tuple<std::size_t, std::size_t, std::size_t, std::size_t, std::size_t>
 *   - 0: pos for '\0'
 *   - 1: adaptor.npos value (for comparison)
 *   - 2: pos for 'g'
 *   - 3: pos for 'T'
 *   - 4: pos for 't'
 */
namespace pmc_split {

inline std::tuple<std::size_t, std::size_t, std::size_t, std::size_t, std::size_t>
buffer_adaptor_find_first_of_positions() {
	std::vector<char> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);

	const auto str = "The quick brown fox jumped over the lazy dog"sv;
	adaptor.write(str.data(), str.size());

	const auto pos0 = adaptor.find_first_of(std::byte('\0'));
	const auto npos = adaptor.npos;
	const auto pos_g = adaptor.find_first_of(std::byte('g'));
	const auto pos_T = adaptor.find_first_of(std::byte('T'));
	const auto pos_t = adaptor.find_first_of(std::byte('t'));

	return {pos0, npos, pos_g, pos_T, pos_t};
}
} // namespace pmc_split
