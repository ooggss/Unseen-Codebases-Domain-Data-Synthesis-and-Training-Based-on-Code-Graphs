

// Split from original test: buffer_adaptor.find_first_of

#include <hexi/buffer_adaptor.h>
#include <vector>
#include <string_view>
#include <cstddef>

using namespace std::literals;

/**
 * @brief Write a string to a buffer_adaptor and query find_first_of for several characters.
 *
 * This function models the functional portion of the original test case:
 * - Writes "The quick brown fox jumped over the lazy dog" into a char buffer via adaptor.write
 * - Queries adaptor.find_first_of for '\\0', 'g', 'T', and 't'
 *
 * @return struct FindFirstOfOutcome
 * Positions returned by find_first_of for each queried character.
 */
struct FindFirstOfOutcome {
  std::size_t pos_null;
  std::size_t pos_g;
  std::size_t pos_T;
  std::size_t pos_t;
  std::size_t npos;
};

FindFirstOfOutcome buffer_adaptor_find_first_of_outcome() {
  std::vector<char> buffer;
  hexi::buffer_adaptor adaptor(buffer);

  const auto str = "The quick brown fox jumped over the lazy dog"sv;
  adaptor.write(str.data(), str.size());

  const auto pos_null = adaptor.find_first_of('\0');
  const auto pos_g = adaptor.find_first_of('g');
  const auto pos_T = adaptor.find_first_of('T');
  const auto pos_t = adaptor.find_first_of('t');

  return FindFirstOfOutcome{
      .pos_null = pos_null,
      .pos_g = pos_g,
      .pos_T = pos_T,
      .pos_t = pos_t,
      .npos = adaptor.npos,
  };
}

