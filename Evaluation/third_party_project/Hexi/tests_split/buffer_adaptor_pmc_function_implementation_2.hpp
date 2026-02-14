
#include <hexi/pmc/buffer_adaptor.h>
#include <vector>
#include <cstdint>

/**
 * @brief Construct an adaptor over a pre-populated buffer and return the adaptor size and buffer size.
 *
 * The function initializes a buffer with one byte, constructs a `buffer_adaptor`,
 * then returns both the adaptor's `size()` and the underlying `buffer.size()`.
 *
 * @return std::pair<std::size_t, std::size_t>
 *   - first: adaptor.size()
 *   - second: buffer.size()
 */
namespace pmc_split {

inline std::pair<std::size_t, std::size_t> buffer_adaptor_size_populated_initial() {
	std::vector<std::uint8_t> buffer{1};
	hexi::pmc::buffer_adaptor adaptor(buffer);
	return {adaptor.size(), buffer.size()};
}
} // namespace pmc_split
