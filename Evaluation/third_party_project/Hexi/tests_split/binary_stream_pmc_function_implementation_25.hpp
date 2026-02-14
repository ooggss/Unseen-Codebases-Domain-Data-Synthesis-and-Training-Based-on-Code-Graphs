
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

struct TotalWriteConsistencyResult {
	std::size_t after_u8;
	std::size_t after_u16;
	std::size_t after_u32;
	std::size_t after_u64;

	std::size_t after_raw;
	std::size_t after_prefixed;
	std::size_t after_prefixed_varint;
	std::size_t after_null_terminated;

	std::size_t after_put_u8;
	std::size_t after_put_u16;
	std::size_t after_put_u32;
	std::size_t after_put_u64;

	std::size_t after_put_array;
	std::size_t after_put_ptr_count;
	std::size_t after_put_iterators;
};

/**
 * @brief Exercises total_write() accounting across multiple write APIs.
 *
 * Writes several integral values via operator<<, then various string encodings (raw, prefixed,
 * prefixed_varint, null_terminated), then uses put<T>() for integrals, and finally writes arrays
 * via put(array), put(ptr,count), and put(iterators). Returns total_write() after each step.
 *
 * @param str The string_view used for the string write operations.
 * @return TotalWriteConsistencyResult The total_write() counters observed after each operation.
 */
TotalWriteConsistencyResult exercise_total_write_consistency(std::string_view str) {
	std::array<char, 1024> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer, hexi::init_empty);
	hexi::pmc::binary_stream stream(adaptor);

	TotalWriteConsistencyResult r{};

	stream << std::uint8_t(0);
	r.after_u8 = stream.total_write();

	stream << std::uint16_t(0);
	r.after_u16 = stream.total_write();

	stream << std::uint32_t(0);
	r.after_u32 = stream.total_write();

	stream << std::uint64_t(0);
	r.after_u64 = stream.total_write();

	stream << hexi::raw(str);
	r.after_raw = stream.total_write();

	stream << hexi::prefixed(str);
	r.after_prefixed = stream.total_write();

	stream << hexi::prefixed_varint(str);
	r.after_prefixed_varint = stream.total_write();

	stream << hexi::null_terminated(str);
	r.after_null_terminated = stream.total_write();

	stream.put<std::uint8_t>(0);
	r.after_put_u8 = stream.total_write();

	stream.put<std::uint16_t>(0);
	r.after_put_u16 = stream.total_write();

	stream.put<std::uint32_t>(0);
	r.after_put_u32 = stream.total_write();

	stream.put<std::uint64_t>(0);
	r.after_put_u64 = stream.total_write();

	std::array<std::uint32_t, 4> data{};
	stream.put(data);
	r.after_put_array = stream.total_write();

	stream.put(data.data(), data.size());
	r.after_put_ptr_count = stream.total_write();

	stream.put(data.begin(), data.end());
	r.after_put_iterators = stream.total_write();

	return r;
}
