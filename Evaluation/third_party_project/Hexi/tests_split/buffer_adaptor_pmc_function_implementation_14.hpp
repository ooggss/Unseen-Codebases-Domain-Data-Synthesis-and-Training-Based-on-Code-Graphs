
#include <hexi/pmc/buffer_adaptor.h>
#include <vector>
#include <cstdint>
#include <tuple>

/**
 * @brief Validate adaptor subscript access and reflect underlying buffer mutation.
 *
 * The function constructs buffer {1,2,3} and adaptor, captures adaptor[0..2],
 * mutates buffer[0] to 4, then captures adaptor[0] again.
 *
 * @return std::tuple<std::byte, std::byte, std::byte, std::byte>
 *   - 0: adaptor[0] before mutation
 *   - 1: adaptor[1]
 *   - 2: adaptor[2]
 *   - 3: adaptor[0] after setting buffer[0] = 4
 */
namespace pmc_split {

inline std::tuple<std::byte, std::byte, std::byte, std::byte> buffer_adaptor_subscript_observations() {
	std::vector<std::uint8_t> buffer{1, 2, 3};
	hexi::pmc::buffer_adaptor adaptor(buffer);

	const std::byte b0 = adaptor[0];
	const std::byte b1 = adaptor[1];
	const std::byte b2 = adaptor[2];

	buffer[0] = 4;
	const std::byte b0_after = adaptor[0];

	return {b0, b1, b2, b0_after};
}
} // namespace pmc_split
