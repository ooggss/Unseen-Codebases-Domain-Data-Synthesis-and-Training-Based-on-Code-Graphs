
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/detail/intrusive_storage.h>
#include <cstddef>
#include <string_view>

/**
 * @brief Demonstrates subscript access/mutation on an intrusive storage buffer.
 *
 * The function:
 * 1) Writes the bytes of the provided string view into `intrusive_storage<8,char>`.
 * 2) Captures the first three bytes via subscript reads.
 * 3) Mutates the first three bytes to 'C', 'D', 'E' via subscript writes.
 * 4) Captures the first three bytes again after mutation.
 *
 * @param str Input string view to write; the function expects at least 3 characters.
 * @return A struct containing the first three bytes before and after mutation.
 */
struct IntrusiveStorageSubscriptResult {
	char before0;
	char before1;
	char before2;
	char after0;
	char after1;
	char after2;
};

IntrusiveStorageSubscriptResult intrusive_storage_subscript_demo(std::string_view str) {
	hexi::detail::intrusive_storage<8, char> buffer;
	buffer.write(str.data(), str.size());

	const char before0 = buffer[0];
	const char before1 = buffer[1];
	const char before2 = buffer[2];

	buffer[0] = 'C';
	buffer[1] = 'D';
	buffer[2] = 'E';

	const char after0 = buffer[0];
	const char after1 = buffer[1];
	const char after2 = buffer[2];

	return IntrusiveStorageSubscriptResult{before0, before1, before2, after0, after1, after2};
}
