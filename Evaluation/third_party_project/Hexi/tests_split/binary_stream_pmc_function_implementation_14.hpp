
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <string>

struct SetErrorStateResult {
	bool initial_truthy;
	bool initial_good;
	hexi::stream_state initial_state;

	bool final_truthy;
	bool final_good;
	hexi::stream_state final_state;
};

/**
 * @brief Verifies that set_error_state() transitions the stream to a user-defined error state.
 *
 * Constructs a stream, captures initial boolean/good/state, then calls set_error_state() and
 * captures final boolean/good/state.
 *
 * @return SetErrorStateResult Initial and final stream status observations.
 */
SetErrorStateResult exercise_set_error_state() {
	std::string buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	SetErrorStateResult res{};
	res.initial_truthy = static_cast<bool>(stream);
	res.initial_good = stream.good();
	res.initial_state = stream.state();

	stream.set_error_state();

	res.final_truthy = static_cast<bool>(stream);
	res.final_good = stream.good();
	res.final_state = stream.state();
	return res;
}
