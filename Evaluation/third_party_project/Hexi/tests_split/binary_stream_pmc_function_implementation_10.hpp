
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <ranges>
#include <vector>

struct FillResult {
	std::size_t size_after_fill_30;
	std::size_t total_write_after_fill_30;
	std::size_t size_after_fill_2_more;
	std::size_t total_write_after_fill_2_more;
	bool all_values_equal_128;
};

/**
 * @brief Uses binary_stream::fill<N>(value) on a vector-backed buffer_adaptor.
 *
 * Fills 30 bytes with value 128, then fills 2 more bytes, checking that the underlying buffer
 * grows accordingly and that all produced bytes equal 128.
 *
 * @return FillResult Sizes and total_write counters after each fill plus a check that all bytes are 128.
 */
FillResult exercise_fill() {
	std::vector<std::uint8_t> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	stream.fill<30>(128);

	FillResult res{};
	res.size_after_fill_30 = buffer.size();
	res.total_write_after_fill_30 = stream.total_write();

	stream.fill<2>(128);
	res.size_after_fill_2_more = buffer.size();
	res.total_write_after_fill_2_more = stream.total_write();

	auto it = std::ranges::find_if(buffer, [](auto i) { return i != 128; });
	res.all_values_equal_128 = (it == buffer.end());
	return res;
}
