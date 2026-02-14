
#include <hexi/pmc/binary_stream.h>
#include <hexi/dynamic_buffer.h>
#include <cstddef>
#include <cstdint>
#include <vector>

struct GetPutResult {
	std::size_t total_read;
	std::size_t total_write;
	std::vector<std::uint8_t> out;
};

/**
 * @brief Writes raw bytes to a stream using put(), then reads them back using get().
 *
 * @param in Bytes to write.
 * @return GetPutResult The total_read/total_write counters after operations and the output bytes read back.
 */
GetPutResult exercise_get_put(const std::vector<std::uint8_t>& in) {
	hexi::dynamic_buffer<32> buffer;
	hexi::pmc::binary_stream stream(buffer);

	std::vector<std::uint8_t> out(in.size());

	stream.put(in.data(), in.size());
	stream.get(out.data(), out.size());

	return GetPutResult{
		.total_read = stream.total_read(),
		.total_write = stream.total_write(),
		.out = std::move(out)
	};
}
