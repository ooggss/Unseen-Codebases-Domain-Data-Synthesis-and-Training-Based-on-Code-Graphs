
#include <hexi/pmc/binary_stream.h>
#include <hexi/dynamic_buffer.h>

struct CanWriteSeekResult {
	bool buffer_can_write_seek;
	bool stream_can_write_seek;
};

/**
 * @brief Compares can_write_seek() capability between a buffer and its binary_stream wrapper.
 *
 * @return CanWriteSeekResult The can_write_seek values reported by the dynamic_buffer and binary_stream.
 */
CanWriteSeekResult exercise_can_write_seek() {
	hexi::dynamic_buffer<32> buffer;
	hexi::pmc::binary_stream stream(buffer);

	return CanWriteSeekResult{
		.buffer_can_write_seek = buffer.can_write_seek(),
		.stream_can_write_seek = stream.can_write_seek()
	};
}
