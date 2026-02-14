
#include <gtest/gtest.h>

// Include function definition (in actual projects, should be included via header file)
#include "buffer_utility_function_implementation_1.hpp"

/**
 * Test Case: src_dest_overlap_end
 *
 * Scenario:
 * - Destination starts at the last byte of the source buffer and has length 1.
 * Expected:
 * - Overlap is detected (true).
 */
TEST(buffer_utility, src_dest_overlap_end) {
  const bool overlaps = src_dest_overlap_end_impl();
  ASSERT_TRUE(overlaps);
}
