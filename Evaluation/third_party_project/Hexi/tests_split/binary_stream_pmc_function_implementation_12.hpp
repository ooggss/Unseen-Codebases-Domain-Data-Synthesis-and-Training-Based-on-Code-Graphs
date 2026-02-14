
#include <hexi/pmc/binary_stream.h>
#include <hexi/dynamic_buffer.h>
#include <cstdint>
#include <limits>

struct PutIntegralLiteralsResult {
	float resultf;
	double resultd;

	std::uint64_t resultu64;
	std::uint32_t resultu32;
	std::uint16_t resultu16;
	std::uint8_t resultu8;

	std::int64_t result64;
	std::int32_t result32;
	std::int16_t result16;
	std::int8_t result8;

	bool stream_truthy;
};

/**
 * @brief Writes numeric literal values of various integral and floating types, then reads them back.
 *
 * Values written:
 * - max() for uint64/uint32/uint16/uint8 and int64/int32/int16/int8
 * - float 1.5f
 * - double 3.0
 *
 * Reads values back in the same order using operator>> and reports the results plus final stream truthiness.
 *
 * @return PutIntegralLiteralsResult The read-back values and whether the stream evaluates to true.
 */
PutIntegralLiteralsResult exercise_put_integral_literals() {
	hexi::dynamic_buffer<64> buffer;
	hexi::pmc::binary_stream stream(buffer);

	stream.put<std::uint64_t>(std::numeric_limits<std::uint64_t>::max());
	stream.put<std::uint32_t>(std::numeric_limits<std::uint32_t>::max());
	stream.put<std::uint16_t>(std::numeric_limits<std::uint16_t>::max());
	stream.put<std::uint8_t>(std::numeric_limits<std::uint8_t>::max());
	stream.put<std::int64_t>(std::numeric_limits<std::int64_t>::max());
	stream.put<std::int32_t>(std::numeric_limits<std::int32_t>::max());
	stream.put<std::int16_t>(std::numeric_limits<std::int16_t>::max());
	stream.put<std::int8_t>(std::numeric_limits<std::int8_t>::max());
	stream.put(1.5f);
	stream.put(3.0);

	PutIntegralLiteralsResult res{};
	stream >> res.resultu64 >> res.resultu32 >> res.resultu16 >> res.resultu8;
	stream >> res.result64 >> res.result32 >> res.result16 >> res.result8;
	stream >> res.resultf >> res.resultd;

	res.stream_truthy = static_cast<bool>(stream);
	return res;
}
