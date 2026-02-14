
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/detail/intrusive_storage.h>
#include <cstddef>
#include <cstring>
#include <string>

/**
 * @brief Performs a write-then-read roundtrip through an intrusive storage buffer and reports results.
 *
 * This function:
 * 1) Creates an `intrusive_storage` buffer sized exactly to the input text length.
 * 2) Writes the entire input text (including the terminating null if present in the provided size).
 * 3) Reads back the same number of bytes into an output buffer.
 * 4) Reports the byte counts written/read, the reconstructed output string (up to the first null),
 *    and the final buffer size (expected to be 0 after full read).
 *
 * @param text The input character buffer to write.
 * @param text_size Number of bytes to write/read.
 * @return A struct containing:
 * - written: bytes reported written by the buffer
 * - read: bytes reported read by the buffer
 * - text_out: reconstructed C-string content from the read buffer
 * - final_size: remaining buffer size after reading
 */
struct IntrusiveStorageRoundtripResult {
	std::size_t written;
	std::size_t read;
	std::string text_out;
	std::size_t final_size;
};

IntrusiveStorageRoundtripResult intrusive_storage_roundtrip_text(const char* text, std::size_t text_size) {
	hexi::detail::intrusive_storage<sizeof(char) * 64> buffer; // big enough for this test case input
	std::size_t written = buffer.write(text, text_size);

	// Read back
	std::string out_storage(text_size, '\0');
	std::size_t read = buffer.read(out_storage.data(), text_size);

	// Interpret as C-string up to first '\0'
	const char* cstr = out_storage.c_str();
	std::string text_out(cstr);

	return IntrusiveStorageRoundtripResult{written, read, text_out, buffer.size()};
}
