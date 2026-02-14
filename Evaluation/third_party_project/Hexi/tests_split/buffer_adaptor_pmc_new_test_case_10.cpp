
#include <gtest/gtest.h>

#include "buffer_adaptor_pmc_function_implementation_10.hpp"

TEST(buffer_adaptor_pmc_split, can_write_seek) {
	ASSERT_TRUE(pmc_split::buffer_adaptor_can_write_seek());
}
