
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <array>

struct StdArraySizeResult {
	bool adaptor_empty;
	std::size_t adaptor_size;
	std::size_t stream_size;
};

/**
 * @brief Validates that a std::array-backed buffer_adaptor initialized as empty reports size 0.
 *
 * @return StdArraySizeResult Whether the adaptor is empty, adaptor.size(), and stream.size().
 */
StdArraySizeResult exercise_std_array_size() {
	std::array<char, 16> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer, hexi::init_empty);
	hexi::pmc::binary_stream stream(adaptor);

	return {
		.adaptor_empty = adaptor.empty(),
		.adaptor_size = adaptor.size(),
		.stream_size = stream.size()
	};
}
