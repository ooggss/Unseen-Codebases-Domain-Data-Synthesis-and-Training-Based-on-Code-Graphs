
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
 * @brief Advances the write pointer, writes a string (including null terminator), then reads past the gap.
 *
 * The function replicates the following behavior:
 * 1) Create `intrusive_storage<32,char>`.
 * 2) Call `advance_write(advance)` to create a gap of `advance` bytes.
 * 3) Write `str.size() + 1` bytes so that a terminating null is included.
 * 4) Read and discard `advance` bytes.
 * 5) Read back `str.size() + 1` bytes and interpret as a C-string.
 *
 * @param str The string view to write; a null terminator is appended by writing `str.size()+1` bytes.
 * @param advance Number of bytes to advance the write pointer before writing the string.
 * @return A struct containing:
 * - size_after_advance: buffer size immediately after advance_write
 * - size_after_write: buffer size after writing the string bytes (gap + string + null)
 * - out: C-string reconstructed after reading past the gap
 */
struct IntrusiveStorageAdvanceWriteResult {
	std::size_t size_after_advance;
	std::size_t size_after_write;
	std::string out;
};

IntrusiveStorageAdvanceWriteResult intrusive_storage_advance_write_roundtrip(std::string_view str,
																			std::size_t advance) {
	hexi::detail::intrusive_storage<32, char> buffer;

	buffer.advance_write(advance);
	const std::size_t size_after_advance = buffer.size();

	buffer.write(str.data(), str.size() + 1);
	const std::size_t size_after_write = buffer.size();

	std::array<char, 128> out{}; // ample
	buffer.read(out.data(), advance);           // skip the 'empty' data
	buffer.read(out.data(), str.size() + 1);    // read string + null

	return IntrusiveStorageAdvanceWriteResult{size_after_advance, size_after_write, std::string(out.data())};
}
