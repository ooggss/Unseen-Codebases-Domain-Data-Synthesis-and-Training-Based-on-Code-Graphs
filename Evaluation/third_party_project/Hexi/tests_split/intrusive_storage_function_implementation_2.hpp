
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/detail/intrusive_storage.h>
#include <array>
#include <cstddef>
#include <string>

/**
 * @brief Writes text into an intrusive storage buffer, skips a prefix, then reads the remainder.
 *
 * This function:
 * 1) Writes the entire `text` buffer into the intrusive storage.
 * 2) Skips `skip_len` bytes from the read position.
 * 3) Reads the remaining bytes into an output buffer and returns the skipped byte count and output string.
 *
 * @param text Input C-string buffer to write.
 * @param text_size Size in bytes to write (may include null terminator).
 * @param skip_len Number of bytes to skip from the front before reading.
 * @return A struct containing:
 * - skipped: bytes reported skipped
 * - remainder: C-string content after skipping, interpreted up to first null terminator
 */
struct IntrusiveStorageSkipResult {
	std::size_t skipped;
	std::string remainder;
};

IntrusiveStorageSkipResult intrusive_storage_skip_and_read(const char* text,
														  std::size_t text_size,
														  std::size_t skip_len) {
	hexi::detail::intrusive_storage<sizeof(char) * 64> buffer; // sufficient for test input
	buffer.write(text, text_size);

	std::size_t skipped = buffer.skip(skip_len);

	// Read remainder (text_size - skip_len bytes) into fixed buffer initialized to zeros.
	std::string out(text_size, '\0');
	buffer.read(out.data(), text_size - skip_len);

	return IntrusiveStorageSkipResult{skipped, std::string(out.c_str())};
}
