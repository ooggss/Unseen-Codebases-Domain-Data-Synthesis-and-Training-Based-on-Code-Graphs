
#include <hexi/pmc/binary_stream.h>
#include <hexi/dynamic_buffer.h>
#include <cstdint>

struct SkipResult {
	std::size_t remaining_size;
	std::size_t remaining_buffer_size;
	std::uint64_t out_value;
	bool stream_empty_after_read;
};

/**
 * @brief Writes two uint64_t values, skips the first, and reads the second.
 *
 * Serializes @p in twice, skips sizeof(uint64_t) bytes to discard the first value,
 * then reads back the remaining value and reports sizes and emptiness.
 *
 * @param in Value to write twice.
 * @return SkipResult Remaining sizes after skip, value read back, and emptiness after read.
 */
SkipResult exercise_skip(std::uint64_t in) {
	hexi::dynamic_buffer<32> buffer;
	hexi::pmc::binary_stream stream(buffer);

	stream << in << in;
	stream.skip(sizeof(in));

	SkipResult res{};
	res.remaining_size = stream.size();
	res.remaining_buffer_size = buffer.size();

	std::uint64_t out{};
	stream >> out;

	res.out_value = out;
	res.stream_empty_after_read = stream.empty();
	return res;
}
