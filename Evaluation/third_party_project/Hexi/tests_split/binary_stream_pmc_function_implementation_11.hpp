
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <vector>

struct ArrayReadResult {
	int first;
	int second;
	int third;
};

/**
 * @brief Writes a C-array of ints to the stream and reads back three ints.
 *
 * @param a Pointer to the first element of an int array.
 * @param n Number of elements in the array (expects at least 3 for this exercise).
 * @return ArrayReadResult The first three integers read back from the stream.
 */
ArrayReadResult exercise_array_write_read_first3(const int* a, std::size_t n) {
	std::vector<char> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	// Write array elements (at least 3)
	for (std::size_t i = 0; i < n && i < 3; ++i) {
		stream << a[i];
	}

	int v = 0;
	stream >> v;
	const int first = v;
	stream >> v;
	const int second = v;
	stream >> v;
	const int third = v;

	return {first, second, third};
}
