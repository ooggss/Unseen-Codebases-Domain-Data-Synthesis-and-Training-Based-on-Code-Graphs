
#include <gtest/gtest.h>

// Include function definition (in actual projects, should be included via header file)
#include "buffer_utility_function_implementation_2.hpp"

/**
 * Test Case: src_dest_overlap_beyond_end
 *
 * Scenario:
 * - Destination starts one past the end of the source buffer.
 * Expected:
 * - No overlap is detected (false).
 */
TEST(buffer_utility, src_dest_overlap_beyond_end) {
  const bool overlaps = src_dest_overlap_beyond_end_impl();
  ASSERT_FALSE(overlaps);
}
