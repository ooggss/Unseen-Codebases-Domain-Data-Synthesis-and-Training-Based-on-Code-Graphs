
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/binary_stream.h>
#include <hexi/null_buffer.h>
#include <cstdint>

namespace test_null_buffer_write_seek {

/**
 * @brief Attempts to perform a write-seek operation on a hexi::null_buffer and returns whether it throws.
 *
 * The original test verifies that calling:
 *   buffer.write_seek(hexi::buffer_seek::sk_absolute, 0)
 * raises hexi::exception for a null_buffer instance. This function performs the same action and
 * reports whether the exception was thrown.
 *
 * @return true if hexi::exception was thrown by write_seek; false otherwise.
 */
inline bool null_buffer_write_seek_throws() {
	hexi::null_buffer buffer;
	hexi::binary_stream stream(buffer); // Constructed to match the original test setup (unused otherwise).

	try {
		buffer.write_seek(hexi::buffer_seek::sk_absolute, 0);
		return false;
	} catch (const hexi::exception&) {
		return true;
	}
}

} // namespace test_null_buffer_write_seek
