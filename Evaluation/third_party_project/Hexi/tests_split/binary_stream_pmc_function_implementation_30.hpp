
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <list>
#include <ranges>
#include <string>
#include <vector>

namespace {

struct PrefixedContainers {
	std::vector<int> vec;
	std::list<int> list;

	void serialise(auto& stream) {
		stream & hexi::prefixed(vec);
		stream & hexi::prefixed(list);
	}

	void serialise(auto& stream) const {
		stream & hexi::prefixed(vec);
		stream & hexi::prefixed(list);
	}

	bool operator==(const PrefixedContainers& rhs) const {
		return vec == rhs.vec && list == rhs.list;
	}
};

} // namespace

struct PrefixedContainersResult {
	std::vector<int> output_primitives;
	std::vector<PrefixedContainers> output_objs;
};

/**
 * @brief Tests prefixed encoding for containers, including nested user objects.
 *
 * Writes:
 * - prefixed(vector<int>) primitives, then reads back into output_primitives.
 * - prefixed(vector<PrefixedContainers>) objects, then reads back into output_objs.
 *
 * @param primitives The primitive vector to write with prefixed encoding.
 * @param objects The vector of PrefixedContainers objects to write with prefixed encoding.
 * @return PrefixedContainersResult The deserialised primitives and objects.
 */
PrefixedContainersResult exercise_prefixed_containers(const std::vector<int>& primitives,
                                                     const std::vector<PrefixedContainers>& objects) {
	std::vector<char> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	stream << hexi::prefixed(primitives);

	std::vector<int> output;
	stream >> hexi::prefixed(output);

	stream << hexi::prefixed(objects);

	std::vector<PrefixedContainers> output_objs;
	stream >> hexi::prefixed(output_objs);

	return {std::move(output), std::move(output_objs)};
}
