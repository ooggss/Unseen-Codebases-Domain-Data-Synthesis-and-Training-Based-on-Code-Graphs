
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/pmc/buffer_adaptor.h>
#include <vector>
#include <cstdint>

/**
 * @brief Create a buffer_adaptor over an empty byte buffer and return its initial size.
 *
 * This function constructs an empty `std::vector<std::uint8_t>`, adapts it with
 * `hexi::pmc::buffer_adaptor`, and returns the adaptor's reported size.
 *
 * @return std::size_t
 *   The initial size of the adaptor (expected to be 0 for an empty buffer).
 */
namespace pmc_split {

inline std::size_t buffer_adaptor_size_empty_initial() {
	std::vector<std::uint8_t> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	return adaptor.size();
}
} // namespace pmc_split
