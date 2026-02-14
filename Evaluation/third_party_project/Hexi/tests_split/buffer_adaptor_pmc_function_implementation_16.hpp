
#include <hexi/pmc/buffer_adaptor.h>
#include <string>
#include <string_view>

using namespace std::literals;

/**
 * @brief Write a string_view into a std::string via buffer_adaptor and return the resulting string.
 *
 * This exercises the optimized `write()` path for buffers that support
 * `resize_and_overwrite` (such as `std::string` in many standard library implementations).
 *
 * @param input The text to write into the string buffer.
 * @return std::string The resulting buffer contents after the write.
 */
namespace pmc_split {

inline std::string buffer_adaptor_write_into_string(std::string_view input) {
	std::string buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	adaptor.write(input.data(), input.size());
	return buffer;
}
} // namespace pmc_split
