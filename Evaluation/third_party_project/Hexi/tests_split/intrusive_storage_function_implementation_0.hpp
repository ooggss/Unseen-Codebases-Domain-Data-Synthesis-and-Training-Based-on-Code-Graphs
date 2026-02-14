
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/detail/intrusive_storage.h>
#include <cstddef>

/**
 * @brief Writes a fixed number of integers into an intrusive storage buffer and validates capacity behavior.
 *
 * This function:
 * 1) Creates an `intrusive_storage` buffer with capacity `sizeof(int) * iterations`.
 * 2) Writes the same integer value `iterations` times, accumulating the number of bytes reported as written.
 * 3) Attempts one additional write beyond capacity, expecting the write to fail (return 0 bytes).
 *
 * It returns the total bytes written after the first loop, the buffer size after filling,
 * the bytes written by the overflow attempt, and the buffer size after the overflow attempt.
 *
 * @param iterations Number of `int` elements to write into the buffer.
 * @param foo_value The integer value whose bytes will be written repeatedly.
 * @return A struct containing:
 * - written_after_loop: total bytes written after `iterations` writes
 * - size_after_loop: buffer size after `iterations` writes
 * - written_overflow_attempt: bytes written by the extra write (expected 0 if full)
 * - size_after_overflow_attempt: buffer size after overflow attempt (expected unchanged)
 */
struct IntrusiveStorageSizeResult {
	std::size_t written_after_loop;
	std::size_t size_after_loop;
	std::size_t written_overflow_attempt;
	std::size_t size_after_overflow_attempt;
};

IntrusiveStorageSizeResult intrusive_storage_size_behavior(int iterations, int foo_value) {
	hexi::detail::intrusive_storage<sizeof(int) * 5> buffer; // capacity fixed to match original test
	int foo = foo_value;
	std::size_t written = 0;

	for (int i = 0; i < iterations; ++i) {
		written += buffer.write(&foo, sizeof(int));
	}

	const std::size_t written_after_loop = written;
	const std::size_t size_after_loop = buffer.size();

	// attempt to exceed capacity - write should return 0
	written = buffer.write(&foo, sizeof(int));
	const std::size_t written_overflow_attempt = written;
	const std::size_t size_after_overflow_attempt = buffer.size();

	return IntrusiveStorageSizeResult{
		written_after_loop,
		size_after_loop,
		written_overflow_attempt,
		size_after_overflow_attempt
	};
}
