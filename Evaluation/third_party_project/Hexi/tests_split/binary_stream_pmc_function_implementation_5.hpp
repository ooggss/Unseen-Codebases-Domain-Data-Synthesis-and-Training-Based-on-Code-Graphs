
#include <hexi/pmc/binary_stream.h>
#include <hexi/dynamic_buffer.h>
#include <vector>

struct ReadWriteVectorResult {
	std::vector<int> first_pass_values;
	std::vector<int> second_pass_out;
	hexi::stream_state final_state;
};

/**
 * @brief Writes a vector<int> to a binary_stream, reads values back individually, then re-reads into a vector.
 *
 * The function:
 * 1) Writes all ints from @p in using stream.put(begin,end).
 * 2) Reads back each int using operator>> and records them.
 * 3) Writes the ints again, then reads them back using stream.get(out.begin,out.end).
 *
 * @param in The vector of integers to round-trip through the stream twice.
 * @return ReadWriteVectorResult The sequence read back in the first pass (per-int),
 *         the vector read back in the second pass (bulk get), and final stream state.
 */
ReadWriteVectorResult exercise_read_write_vector(const std::vector<int>& in) {
	hexi::dynamic_buffer<32> buffer;
	hexi::pmc::binary_stream stream(buffer);

	stream.put(in.begin(), in.end());

	ReadWriteVectorResult res{};
	res.first_pass_values.reserve(in.size());

	for (auto expected : in) {
		int output = -1;
		stream >> output;
		(void)expected;
		res.first_pass_values.push_back(output);
	}

	stream.put(in.begin(), in.end());
	std::vector<int> out(in.size());
	stream.get(out.begin(), out.end());

	res.second_pass_out = std::move(out);
	res.final_state = stream.state();
	return res;
}
