

// Split from original test: buffer_adaptor.string_buffer

#include <hexi/buffer_adaptor.h>
#include <string>
#include <string_view>

using namespace std::literals;

/**
 * @brief Write a string_view into a std::string via buffer_adaptor and return the resulting string.
 *
 * This function models the functional portion of the original test case:
 * - Creates a std::string buffer and adaptor
 * - Writes the contents of a string_view into it
 * - Returns the resulting buffer content
 *
 * @return std::string
 * The final contents of the string buffer (expected to equal the input string_view).
 */
std::string buffer_adaptor_write_into_string_buffer() {
  std::string buffer;
  hexi::buffer_adaptor adaptor(buffer);

  const auto str = "The quick brown fox jumped over the lazy dog"sv;
  adaptor.write(str.data(), str.size());

  return buffer;
}

