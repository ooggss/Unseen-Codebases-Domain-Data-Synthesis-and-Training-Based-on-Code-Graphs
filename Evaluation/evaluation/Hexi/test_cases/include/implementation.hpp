#include <hexi/hexi.h>
#include <vector>
#include <string>
#include <cstdint>

struct NetworkPacket {
    uint32_t packet_id;
    std::string username;
    std::vector<uint32_t> scores;
    std::string metadata;
    
    void serialise(auto& adaptor) const {
        adaptor(packet_id, username);
        adaptor & hexi::prefixed(scores);
        adaptor & hexi::null_terminated(metadata);
    }
};

std::vector<uint8_t> serialize_packet(const NetworkPacket& packet) {
    std::vector<uint8_t> buffer;
    hexi::buffer_adaptor adaptor(buffer);
    hexi::binary_stream stream(adaptor);
    
    stream.serialise(packet);
    
    return buffer;
}