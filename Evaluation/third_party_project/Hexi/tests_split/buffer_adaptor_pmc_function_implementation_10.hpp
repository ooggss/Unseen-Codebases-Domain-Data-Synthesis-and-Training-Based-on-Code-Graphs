
#include <hexi/pmc/buffer_adaptor.h>
#include <vector>

/**
 * @brief Determine whether a buffer_adaptor supports write seeking.
 *
 * Constructs an empty buffer and adaptor, then returns `adaptor.can_write_seek()`.
 *
 * @return bool
 *   True if write seeking is supported by this adaptor/buffer type.
 */
namespace pmc_split {

inline bool buffer_adaptor_can_write_seek() {
	std::vector<std::uint8_t> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	return adaptor.can_write_seek();
}

} // namespace pmc_split
