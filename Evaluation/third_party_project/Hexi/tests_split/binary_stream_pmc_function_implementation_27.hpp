
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <array>
#include <cstdint>

struct EndiannessOverrideMismatchResult {
	std::uint64_t le_written_be_read;
	std::uint64_t be_written_le_read;
};

/**
 * @brief Writes uint64_t in one endianness and reads in the opposite endianness to ensure mismatch.
 *
 * @param input The value to write.
 * @return EndiannessOverrideMismatchResult Outputs read back when endianness is mismatched (should differ from input).
 */
EndiannessOverrideMismatchResult exercise_endianness_override_mismatch(std::uint64_t input) {
	std::array<char, 16> buffer{};
	hexi::pmc::buffer_adaptor adaptor(buffer, hexi::init_empty);
	hexi::pmc::binary_stream stream(adaptor);

	std::uint64_t out1 = 0, out2 = 0;

	stream << hexi::endian::le(input);
	stream >> hexi::endian::be(out1);

	stream << hexi::endian::be(input);
	stream >> hexi::endian::le(out2);

	return {out1, out2};
}
