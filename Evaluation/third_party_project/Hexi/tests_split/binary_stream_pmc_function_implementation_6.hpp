
#include <hexi/pmc/binary_stream.h>
#include <hexi/dynamic_buffer.h>
#include <cstddef>
#include <cstdint>

struct ClearResult {
	bool stream_non_empty_after_write;
	bool buffer_non_empty_after_write;
	bool stream_empty_after_skip;
	bool buffer_empty_after_skip;
};

/**
 * @brief Demonstrates clearing a stream by skipping all remaining bytes.
 *
 * Writes a 32-bit literal (0xBADF00D) to the stream, then skips stream.size() bytes,
 * which should consume all pending data and leave both stream and underlying buffer empty.
 *
 * @return ClearResult Flags describing emptiness before and after skipping.
 */
ClearResult exercise_clear_via_skip_all() {
	hexi::dynamic_buffer<32> buffer;
	hexi::pmc::binary_stream stream(buffer);

	stream << 0xBADF00D;

	ClearResult res{};
	res.stream_non_empty_after_write = !stream.empty();
	res.buffer_non_empty_after_write = !buffer.empty();

	stream.skip(stream.size());

	res.stream_empty_after_skip = stream.empty();
	res.buffer_empty_after_skip = buffer.empty();
	return res;
}
