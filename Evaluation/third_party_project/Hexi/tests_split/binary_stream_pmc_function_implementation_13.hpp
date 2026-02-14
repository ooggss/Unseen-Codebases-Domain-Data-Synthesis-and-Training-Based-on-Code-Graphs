
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <string>
#include <string_view>

struct StringViewWriteResult {
	std::string res;
};

/**
 * @brief Writes a std::string_view to the stream and reads it back into a std::string.
 *
 * @param view The string_view to serialize.
 * @return StringViewWriteResult The read-back string.
 */
StringViewWriteResult exercise_string_view_write(std::string_view view) {
	std::vector<char> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	// Write the string view (library adds a size prefix)
	stream << view;

	// Read back using the same format (with size prefix)
	std::string res;
	stream >> res;

	// Remove trailing null if present (library may add it)
	if (!res.empty() && res.back() == '\0') {
		res.pop_back();
	}

	return {res};
}
