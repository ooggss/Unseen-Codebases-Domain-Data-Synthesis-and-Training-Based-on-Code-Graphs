
#include <hexi/pmc/buffer_adaptor.h>
#include <vector>
#include <cstdint>
#include <tuple>

/**
 * @brief Obtain read pointers at successive positions and return the dereferenced values.
 *
 * The function constructs a buffer {1,2,3}, then:
 * - reads the value pointed to by `read_ptr()` (position 0)
 * - skips 1, reads value at position 1
 * - skips 1, reads value at position 2
 *
 * @return std::tuple<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>
 *   Contains pairs (observed, expected) for indices 0..2:
 *   - 0: observed0, 1: expected0
 *   - 2: observed1, 3: expected1
 *   - 4: observed2, 5: expected2
 */
namespace pmc_split {

inline std::tuple<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>
buffer_adaptor_read_ptr_sequence() {
	std::vector<std::uint8_t> buffer{1, 2, 3};
	hexi::pmc::buffer_adaptor adaptor(buffer);

	auto ptr0 = adaptor.read_ptr();
	const std::uint8_t obs0 = static_cast<std::uint8_t>(*ptr0);
	const std::uint8_t exp0 = buffer[0];

	adaptor.skip(1);
	auto ptr1 = adaptor.read_ptr();
	const std::uint8_t obs1 = static_cast<std::uint8_t>(*ptr1);
	const std::uint8_t exp1 = buffer[1];

	adaptor.skip(1);
	auto ptr2 = adaptor.read_ptr();
	const std::uint8_t obs2 = static_cast<std::uint8_t>(*ptr2);
	const std::uint8_t exp2 = buffer[2];

	return {obs0, exp0, obs1, exp1, obs2, exp2};
}
} // namespace pmc_split
