
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/binary_stream.h>
#include <hexi/null_buffer.h>
#include <string_view>
#include <cstdint>
#include <utility>

namespace test_null_buffer_write_size {

/**
 * @brief Writes multiple primitive values and a null-terminated string to a binary stream backed by a
 *        hexi::null_buffer, and returns the observed total byte counts after each write.
 *
 * This function demonstrates that:
 * - Writing integral types increases the stream's total_write() by the size of the written type.
 * - Writing a null-terminated string increases the count by (string length + 1) due to the terminator.
 * - The underlying hexi::null_buffer remains empty because it discards written data.
 *
 * @param str The string content to be written as a null-terminated sequence.
 * @return A pair where:
 *         - first: an array of total_write() values after each write operation, in order:
 *                  uint8_t, uint16_t, uint32_t, uint64_t, null-terminated string.
 *         - second: whether the underlying null_buffer is empty after all writes.
 */
inline std::pair<std::array<std::size_t, 5>, bool> write_and_measure_total_bytes(std::string_view str) {
	hexi::null_buffer buffer;
	hexi::binary_stream stream(buffer);

	std::array<std::size_t, 5> totals{};

	stream << std::uint8_t(0);
	totals[0] = stream.total_write();

	stream << std::uint16_t(0);
	totals[1] = stream.total_write();

	stream << std::uint32_t(0);
	totals[2] = stream.total_write();

	stream << std::uint64_t(0);
	totals[3] = stream.total_write();

	stream << hexi::null_terminated(str);
	totals[4] = stream.total_write();

	return {totals, buffer.empty()};
}

} // namespace test_null_buffer_write_size
