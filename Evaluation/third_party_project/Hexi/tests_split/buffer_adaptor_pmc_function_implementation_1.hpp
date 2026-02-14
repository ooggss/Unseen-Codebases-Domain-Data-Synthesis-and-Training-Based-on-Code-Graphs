
#include <hexi/pmc/buffer_adaptor.h>
#include <vector>
#include <cstdint>

/**
 * @brief Check `buffer_adaptor::empty()` before and after writing one byte.
 *
 * The function:
 * 1) Creates an empty byte buffer and adaptor, records whether it is empty.
 * 2) Appends a byte to the underlying buffer and advances the adaptor's write position.
 * 3) Records whether the adaptor is empty after the write.
 *
 * @return std::pair<bool, bool>
 *   - first: emptiness state before writing (expected true)
 *   - second: emptiness state after writing one byte (expected false)
 */
namespace pmc_split {

inline std::pair<bool, bool> buffer_adaptor_empty_before_after_one_write() {
	std::vector<std::uint8_t> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);

	const bool empty_before = adaptor.empty();

	buffer.emplace_back(1);
	adaptor.advance_write(1);

	const bool empty_after = adaptor.empty();
	return {empty_before, empty_after};
}
} // namespace pmc_split
