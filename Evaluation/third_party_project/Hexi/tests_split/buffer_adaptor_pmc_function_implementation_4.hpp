
#include <hexi/pmc/buffer_adaptor.h>
#include <vector>
#include <cstdint>
#include <utility>

/**
 * @brief Read one byte from an adaptor and report the resulting adaptor size and read value.
 *
 * The function initializes a buffer {1,2,3}, reads one byte into `value`,
 * and returns:
 * - the adaptor's size after the read
 * - the read byte value
 * - the original buffer size (for computing expected remaining size)
 *
 * @return std::tuple<std::size_t, std::uint8_t, std::size_t>
 *   - 0: adaptor.size() after reading 1 byte
 *   - 1: value read (expected 1)
 *   - 2: original buffer.size() (expected 3)
 */
namespace pmc_split {

inline std::tuple<std::size_t, std::uint8_t, std::size_t> buffer_adaptor_read_one_result() {
	std::vector<std::uint8_t> buffer{1, 2, 3};
	hexi::pmc::buffer_adaptor adaptor(buffer);

	std::uint8_t value = 0;
	adaptor.read(&value, 1);

	return {adaptor.size(), value, buffer.size()};
}
} // namespace pmc_split
