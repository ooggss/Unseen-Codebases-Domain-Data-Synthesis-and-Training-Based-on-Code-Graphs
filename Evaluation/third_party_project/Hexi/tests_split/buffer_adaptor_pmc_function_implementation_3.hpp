
#include <hexi/pmc/buffer_adaptor.h>
#include <vector>
#include <cstdint>

/**
 * @brief Validate that adaptor size tracks buffer growth after advancing write.
 *
 * The function:
 * 1) Creates a buffer with 5 bytes and constructs an adaptor.
 * 2) Captures adaptor.size() and buffer.size() initially.
 * 3) Appends one byte to the buffer, calls `advance_write(1)`,
 *    then captures adaptor.size() and buffer.size() again.
 *
 * @return std::array<std::size_t, 4>
 *   Values in order:
 *   - [0] initial adaptor.size()
 *   - [1] initial buffer.size()
 *   - [2] after-append adaptor.size()
 *   - [3] after-append buffer.size()
 */
namespace pmc_split {

inline std::array<std::size_t, 4> buffer_adaptor_resize_match_sizes() {
	std::vector<std::uint8_t> buffer{1, 2, 3, 4, 5};
	hexi::pmc::buffer_adaptor adaptor(buffer);

	const std::size_t initial_adaptor_size = adaptor.size();
	const std::size_t initial_buffer_size = buffer.size();

	buffer.emplace_back(6);
	adaptor.advance_write(1);

	const std::size_t after_adaptor_size = adaptor.size();
	const std::size_t after_buffer_size = buffer.size();

	return {initial_adaptor_size, initial_buffer_size, after_adaptor_size, after_buffer_size};
}
} // namespace pmc_split
