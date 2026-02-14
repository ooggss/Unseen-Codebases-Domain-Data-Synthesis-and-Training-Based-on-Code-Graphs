#include <gtest/gtest.h>
#include <hexi/hexi.h>
#include <vector>
#include <string>
#include <cstdint>

// Include the implementation
#include "implementation.hpp"

TEST(NetworkPacket, Serialize) {
    NetworkPacket packet;
    packet.packet_id = 12345;
    packet.username = "testuser";
    packet.scores = {100, 200, 300, 400};
    packet.metadata = "test metadata";
    
    auto buffer = serialize_packet(packet);
    ASSERT_FALSE(buffer.empty());
    EXPECT_GT(buffer.size(), 0);
}

TEST(NetworkPacket, SerializeLongString) {
    NetworkPacket packet;
    packet.packet_id = 777;
    packet.username = "very_long_username_that_should_work_correctly";
    packet.scores = {1, 2, 3};
    packet.metadata = "metadata with special chars: !@#$%^&*()";
    
    auto buffer = serialize_packet(packet);
    ASSERT_FALSE(buffer.empty());
}