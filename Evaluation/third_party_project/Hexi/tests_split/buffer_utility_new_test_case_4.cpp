
#include <gtest/gtest.h>

// Include function definition (in actual projects, should be included via header file)
#include "buffer_utility_function_implementation_4.hpp"

/**
 * Test Case: src_dest_overlap_no_overlap
 *
 * Scenario:
 * - Source and destination regions are from two different buffers.
 * Expected:
 * - No overlap is detected (false).
 */
TEST(buffer_utility, src_dest_overlap_no_overlap) {
  const bool overlaps = src_dest_overlap_no_overlap_impl();
  ASSERT_FALSE(overlaps);
}
