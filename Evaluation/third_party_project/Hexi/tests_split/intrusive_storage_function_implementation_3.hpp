
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/detail/intrusive_storage.h>
#include <array>
#include <cstddef>
#include <string>
#include <string_view>

/**
 * @brief Writes a string_view into an intrusive storage buffer, reads it back, and reports state.
 *
 * The function:
 * 1) Writes `str.size()` bytes from `str.data()` into a `intrusive_storage<128,char>`.
 * 2) Reads exactly `str.size()` bytes back into an output array.
 * 3) Returns the buffer size after write, the read-back string, and whether the buffer is empty after read.
 *
 * @param str The input string view to write (no null terminator is required/written).
 * @return A struct containing:
 * - size_after_write: buffer size after write (expected == str.size())
 * - out: string reconstructed from read bytes (length == str.size())
 * - empty_after_read: whether buffer.size() == 0 after the read
 */
struct IntrusiveStorageStringViewResult {
	std::size_t size_after_write;
	std::string out;
	bool empty_after_read;
};

IntrusiveStorageStringViewResult intrusive_storage_write_read_string_view(std::string_view str) {
	hexi::detail::intrusive_storage<128, char> buffer;

	buffer.write(str.data(), str.size());
	const std::size_t size_after_write = buffer.size();

	std::array<char, 128> out{};
	buffer.read(out.data(), str.size());

	std::string out_str(out.data(), str.size());
	const bool empty_after_read = (buffer.size() == 0);

	return IntrusiveStorageStringViewResult{size_after_write, out_str, empty_after_read};
}
