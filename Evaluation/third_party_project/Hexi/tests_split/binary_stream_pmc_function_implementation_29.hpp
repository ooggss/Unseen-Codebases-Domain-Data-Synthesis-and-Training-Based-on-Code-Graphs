
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <list>
#include <set>
#include <string>
#include <vector>

namespace {

struct Complex {
	std::string str = "Hello, world!";
	std::vector<int> vec{1, 2, 3, 4, 5};
	std::list<int> list{6, 7, 8, 9, 10};
	std::set<int> set{11, 12, 13, 14, 15};

	void serialise(auto& stream) {
		stream(str, vec, list, set);
	}
};

} // namespace

struct IterableContainersResult {
	std::size_t bytes_after_primitives;
	std::size_t adaptor_size_after_primitives;
	std::size_t backing_buffer_size_after_primitives;

	std::vector<int> primitives_read_back;

	std::string hello;
	std::string world;

	std::string complex_str;
	std::vector<int> complex_numbers; // 1..15 in read order
};

/**
 * @brief Exercises streaming of iterable containers and an object with a serialise() method.
 *
 * Writes:
 * 1) vector<int> primitives
 * 2) vector<string> strings
 * Then reads back the primitives via get<int>() and the strings via operator>>.
 * Then writes a Complex object and reads back its string and all contained integers via get<int>() in order.
 *
 * @param primitives The primitive integers to write first.
 * @param strings Two strings to write after primitives (expects size 2).
 * @return IterableContainersResult Captured sizes after primitives, read-back primitives and strings,
 *         and the Complex object's string plus all integers read in order.
 */
IterableContainersResult exercise_iterable_containers(const std::vector<int>& primitives,
                                                     const std::vector<std::string>& strings) {
	std::vector<char> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	stream << primitives;

	IterableContainersResult r{};
	r.bytes_after_primitives = stream.total_write();
	r.adaptor_size_after_primitives = adaptor.size();
	r.backing_buffer_size_after_primitives = buffer.size();

	stream << strings;

	// read back primitives
	r.primitives_read_back.reserve(primitives.size());
	for (std::size_t i = 0; i < primitives.size(); ++i) {
		r.primitives_read_back.push_back(stream.get<int>());
	}

	// read back strings
	stream >> r.hello >> r.world;

	// write/read complex object
	Complex obj_in;
	stream << obj_in;

	stream >> r.complex_str;
	for (int i = 0; i < 15; ++i) {
		r.complex_numbers.push_back(stream.get<int>());
	}

	return r;
}
