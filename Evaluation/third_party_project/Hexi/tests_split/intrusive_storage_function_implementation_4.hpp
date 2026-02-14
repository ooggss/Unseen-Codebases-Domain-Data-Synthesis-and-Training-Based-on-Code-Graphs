
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/detail/intrusive_storage.h>
#include <array>
#include <cstddef>

/**
 * @brief Writes an array of 4 integers to an intrusive storage buffer and reads it back.
 *
 * The function:
 * 1) Writes the raw bytes of the input integer array into `intrusive_storage<128,char>`.
 * 2) Reads back the same number of bytes into an output array of integers.
 * 3) Returns buffer size after write, the output array, and whether buffer is empty after read.
 *
 * @param in Input array of 4 integers.
 * @return A struct containing:
 * - size_after_write: buffer size after write (expected == sizeof(in))
 * - out: integers read back from the buffer
 * - empty_after_read: whether buffer.size() == 0 after the read
 */
struct IntrusiveStorageIntsResult {
	std::size_t size_after_write;
	std::array<int, 4> out;
	bool empty_after_read;
};

IntrusiveStorageIntsResult intrusive_storage_write_read_ints(const std::array<int, 4>& in) {
	hexi::detail::intrusive_storage<128, char> buffer;

	buffer.write(in.data(), sizeof(in));
	const std::size_t size_after_write = buffer.size();

	std::array<int, 4> out{};
	buffer.read(out.data(), sizeof(out));

	const bool empty_after_read = (buffer.size() == 0);
	return IntrusiveStorageIntsResult{size_after_write, out, empty_after_read};
}
