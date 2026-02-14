
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <array>
#include <cstdint>

struct EndiannessOverrideMatchResult {
	std::uint64_t le_out;
	std::uint64_t be_out;
};

/**
 * @brief Writes and reads uint64_t with explicit endianness overrides where write and read match.
 *
 * @param input The uint64_t value to round-trip with both little-endian and big-endian overrides.
 * @return EndiannessOverrideMatchResult The outputs read back for LE and BE operations.
 */
EndiannessOverrideMatchResult exercise_endianness_override_match(std::uint64_t input) {
	std::array<char, 16> buffer{};
	hexi::pmc::buffer_adaptor adaptor(buffer, hexi::init_empty);
	hexi::pmc::binary_stream stream(adaptor);

	std::uint64_t le_out = 0, be_out = 0;

	stream << hexi::endian::le(input);
	stream >> hexi::endian::le(le_out);

	stream << hexi::endian::be(input);
	stream >> hexi::endian::be(be_out);

	return {le_out, be_out};
}
