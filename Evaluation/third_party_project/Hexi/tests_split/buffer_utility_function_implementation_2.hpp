
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
 * @brief Checks whether a destination region that starts exactly at the end of
 *        a buffer overlaps with the buffer region.
 *
 * This function constructs a 10-byte buffer and defines:
 * - Source: full buffer region.
 * - Dest: a 1-byte region starting at buffer_end (one past the last byte).
 *
 * @return true if the regions overlap; otherwise false.
 */
bool src_dest_overlap_beyond_end_impl() {
  std::array<std::uint8_t, 10> buffer{};
  const auto end = buffer.data() + buffer.size();
  return region_overlap(buffer.data(), buffer.size(), end, 1);
}
