
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace {

struct Foo {
	std::uint16_t x;
	std::uint32_t y;
	std::uint64_t z;
	std::string str;

	void serialise(auto& stream) {
		stream(x, y, z, hexi::null_terminated(str));
		stream & hexi::endian::be(x);
	}

	void serialise(auto& stream) const {
		stream(x, y, z, hexi::null_terminated(str));
		stream & hexi::endian::be(x);
	}

	bool operator==(const Foo& rhs) const {
		return x == rhs.x && y == rhs.y && z == rhs.z && str == rhs.str;
	}
};

} // namespace

struct ExperimentalSerialiseResult {
	std::size_t total_write;
	std::size_t total_read;
	std::size_t remaining_size;
	bool stream_truthy;
	Foo output;
};

/**
 * @brief Serialises and deserialises a Foo object using binary_stream's experimental serialise API.
 *
 * Writes @p input via stream.serialise(), checks bytes written, then deserialises into a fresh Foo and
 * reports bytes read, remaining size, stream truthiness, and the output object.
 *
 * @param input The Foo object to serialise.
 * @return ExperimentalSerialiseResult Metrics and the deserialised output object.
 */
ExperimentalSerialiseResult exercise_experimental_serialise(const Foo& input) {
	std::vector<unsigned char> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	stream.serialise(input);
	const std::size_t total_write = stream.total_write();

	Foo output{};
	stream.deserialise(output);

	return ExperimentalSerialiseResult{
		.total_write = total_write,
		.total_read = stream.total_read(),
		.remaining_size = stream.size(),
		.stream_truthy = static_cast<bool>(stream),
		.output = std::move(output)
	};
}
