
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/shared.h>
#include <array>
#include <cstddef>
#include <cstdint>

using namespace hexi::detail;

/**
 * @brief Checks whether a source and destination memory region overlap when both
 *        regions begin at the start of the same buffer.
 *
 * This function constructs a 10-byte buffer and then checks for overlap between:
 * - Source:  [buffer.data(), buffer.data() + buffer.size())
 * - Dest:    [buffer.data(), buffer.data() + buffer.size())
 *
 * @return true if the regions overlap; otherwise false.
 */
bool src_dest_overlap_start_impl() {
  std::array<std::uint8_t, 10> buffer{};
  return region_overlap(buffer.data(), buffer.size(), buffer.data(), buffer.size());
}
