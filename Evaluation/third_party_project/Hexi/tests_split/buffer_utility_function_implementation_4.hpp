
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/shared.h>
#include <array>
#include <cstdint>

using namespace hexi::detail;

/**
 * @brief Checks whether two distinct buffers overlap in memory.
 *
 * This function constructs two separate 10-byte buffers and checks for overlap
 * between:
 * - Source: buffer1 full region
 * - Dest:   buffer2 full region
 *
 * @return true if the regions overlap; otherwise false.
 */
bool src_dest_overlap_no_overlap_impl() {
  std::array<std::uint8_t, 10> buffer{}, buffer2{};
  return region_overlap(buffer.data(), buffer.size(), buffer2.data(), buffer2.size());
}
