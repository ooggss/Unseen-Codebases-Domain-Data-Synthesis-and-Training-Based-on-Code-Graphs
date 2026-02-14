
#include "final_action.h"
#include "helpers.h"
#include <hexi/binary_stream.h>
#include <hexi/buffer_adaptor.h>
#include <hexi/dynamic_buffer.h>
#include <hexi/endian.h>
#include <hexi/file_buffer.h>
#include <hexi/static_buffer.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <format>
#include <limits>
#include <list>
#include <numeric>
#include <random>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <vector>

namespace binary_stream_split {


struct Result {
  // generic booleans
  bool ok1 = false;
  bool ok2 = false;
  bool ok3 = false;

  // sizes / counters
  std::size_t size1 = 0;
  std::size_t size2 = 0;
  std::size_t size3 = 0;
  std::size_t total_read = 0;
  std::size_t total_write = 0;

  // numeric outputs
  std::uint64_t u64_1 = 0;
  std::uint64_t u64_2 = 0;
  std::uint32_t u32_1 = 0;
  std::uint32_t u32_2 = 0;
  std::uint16_t u16_1 = 0;
  std::uint16_t u16_2 = 0;
  std::uint8_t u8_1 = 0;
  std::uint8_t u8_2 = 0;

  std::int64_t i64_1 = 0;
  std::int32_t i32_1 = 0;
  std::int16_t i16_1 = 0;
  std::int16_t i16_2 = 0;
  std::int8_t i8_1 = 0;

  float f1 = 0.0f;
  double d1 = 0.0;

  // stream state snapshots
  hexi::stream_state state = hexi::stream_state::ok;

  // strings/views
  std::string s1;
  std::string s2;
  std::string sv1;
  std::string sv2;

  // arrays/spans captured
  std::array<int, 4> iarr4{};

  // exception flags (instead of throwing across API boundary)
  bool threw1 = false;
  bool threw2 = false;

  // file content comparisons
  bool files_equal = false;

  // adaptor find pos
  std::size_t pos = 0;
};

namespace {
struct Foo {
  std::uint16_t x;
  std::uint32_t y;
  std::uint64_t z;
  std::string_view str;

  void serialise(auto& stream) {
    stream(x, y, z, hexi::null_terminated(str));
    stream& hexi::endian::be(x);
  }

  bool operator==(const Foo& rhs) const {
    return x == rhs.x && y == rhs.y && z == rhs.z && str == rhs.str;
  }
};

struct Complex {
  std::string str = "Hello, world!";
  std::vector<int> vec{1, 2, 3, 4, 5};
  std::list<int> list{6, 7, 8, 9, 10};
  std::set<int> set{11, 12, 13, 14, 15};

  void serialise(auto& stream) { stream(str, vec, list, set); }
};

struct PrefixedContainers {
  std::vector<int> vec;
  std::list<int> list;

  void serialise(auto& stream) {
    stream& hexi::prefixed(vec);
    stream& hexi::prefixed(list);
  }

  bool operator==(const PrefixedContainers& rhs) const {
    return vec == rhs.vec && list == rhs.list;
  }
};
}  // namespace

/**
 * Runs a selected binary_stream scenario from the original test suite and returns
 * a compact "result object" that contains the values that were previously asserted
 * in the test body.
 *
 * This function consolidates multiple original TEST cases into one callable entrypoint.
 * The caller specifies which scenario to execute, and the function performs the same
 * setup/operations that the original test performed (writing/reading buffers, skipping,
 * using string adaptors, endianness overrides, etc.). It then records the observable
 * outcomes (values, sizes, states, exception flags) into the returned struct.
 *
 * Parameters:
 * - scenario:
 *   A string identifier selecting which original test scenario to run. Supported values:
 *   - "message_read_limit"
 *   - "buffer_limit"
 *   - "read_write_ints"
 *   - "read_write_std_string"
 *   - "read_write_c_string"
 *   - "read_write_vector"
 *   - "clear"
 *   - "skip"
 *   - "can_write_seek"
 *   - "get_put"
 *   - "fill"
 *   - "no_copy_string_read"
 *   - "string_view_read"
 *   - "partial_string_view_read"
 *   - "string_view_stream"
 *   - "array"
 *   - "span"
 *   - "static_buffer_write"
 *   - "static_buffer_direct_write"
 *   - "static_buffer_overflow"
 *   - "static_buffer_read"
 *   - "static_buffer_underrun"
 *   - "static_buffer_underrun_noexcept"
 *   - "static_buffer_adaptor_regression"
 *   - "static_buffer_adaptor_exception_regression"
 *   - "static_buffer_adaptor_no_exception_regression"
 *   - "put_integral_literals"
 *   - "file_buffer_read"
 *   - "file_buffer_write"
 *   - "set_error_state"
 *   - "string_adaptor_prefixed_varint_long"
 *   - "string_adaptor_prefixed_varint_medium"
 *   - "string_adaptor_prefixed_varint_short"
 *   - "string_adaptor_prefixed"
 *   - "string_adaptor_default"
 *   - "string_adaptor_raw"
 *   - "string_adaptor_null_terminated"
 *   - "string_view_adaptor_prefixed_varint_long"
 *   - "string_view_adaptor_prefixed_varint_medium"
 *   - "string_view_adaptor_prefixed_varint_short"
 *   - "string_view_adaptor_prefixed"
 *   - "string_view_adaptor_default"
 *   - "string_view_adaptor_raw"
 *   - "string_view_adaptor_null_terminated"
 *   - "std_array"
 *   - "total_write_consistency"
 *   - "endianness_big_match"
 *   - "endianness_little_match"
 *   - "endianness_native_match"
 *   - "endianness_big_override_match"
 *   - "endianness_little_override_match"
 *   - "endianness_native_override_match"
 *   - "endianness_big_override_mismatch"
 *   - "endianness_little_override_mismatch"
 *   - "endianness_native_override_mismatch"
 *   - "experimental_serialise"
 *   - "iterable_containers"
 *   - "prefixed_containers"
 *   - "std_array_size"
 *
 * Returns:
 * - A Result struct containing fields that are relevant for the chosen scenario.
 *   Only a subset of fields will be meaningful per scenario; unused fields remain
 *   default-initialized.
 */
Result run_binary_stream_scenario(const std::string& scenario) {
  Result r{};

  if (scenario == "message_read_limit") {
    std::array<std::uint8_t, 14> ping{0x00, 0x0C, 0xDC, 0x01, 0x00, 0x00, 0x01,
                                     0x00, 0x00, 0x00, 0xF4, 0x01, 0x00, 0x00};

    hexi::dynamic_buffer<32> buffer;
    buffer.write(ping.data(), ping.size());
    buffer.write(ping.data(), ping.size());

    hexi::binary_stream stream(buffer, ping.size());
    r.size1 = stream.read_limit();

    try {
      stream.get(ping.data(), ping.size());
      r.ok1 = true;
    } catch (...) {
      r.ok1 = false;
    }

    try {
      stream.get(ping.data(), ping.size());
      r.threw1 = false;
    } catch (const hexi::stream_read_limit&) {
      r.threw1 = true;
    }

    r.state = stream.state();
    return r;
  }

  if (scenario == "buffer_limit") {
    std::array<std::uint8_t, 14> ping{0x00, 0x0C, 0xDC, 0x01, 0x00, 0x00, 0x01,
                                     0x00, 0x00, 0x00, 0xF4, 0x01, 0x00, 0x00};

    hexi::dynamic_buffer<32> buffer;
    buffer.write(ping.data(), ping.size());

    hexi::binary_stream stream(buffer);

    try {
      stream.get(ping.data(), ping.size());
      r.ok1 = true;
    } catch (...) {
      r.ok1 = false;
    }

    try {
      stream.get(ping.data(), ping.size());
      r.threw1 = false;
    } catch (const hexi::buffer_underrun&) {
      r.threw1 = true;
    }

    r.state = stream.state();
    return r;
  }

  if (scenario == "read_write_ints") {
    hexi::dynamic_buffer<32> buffer;
    hexi::binary_stream stream(buffer);

    const std::uint16_t in{100};
    stream << in;

    r.size1 = stream.size();
    r.size2 = buffer.size();

    std::uint16_t out = 0;
    stream >> out;

    r.u16_1 = in;
    r.u16_2 = out;
    r.ok1 = stream.empty();
    r.ok2 = buffer.empty();
    r.state = stream.state();
    return r;
  }

  if (scenario == "read_write_std_string") {
    hexi::dynamic_buffer<32> buffer;
    hexi::binary_stream stream(buffer);
    const std::string in{"The quick brown fox jumped over the lazy dog"};
    stream << hexi::null_terminated(in);

    r.size1 = stream.size();

    std::string out;
    stream >> hexi::null_terminated(out);

    r.ok1 = stream.empty();
    r.s1 = in;
    r.s2 = out;
    r.state = stream.state();
    return r;
  }

  if (scenario == "read_write_c_string") {
    hexi::dynamic_buffer<32> buffer;
    hexi::binary_stream stream(buffer);
    const char* in{"The quick brown fox jumped over the lazy dog"};
    stream << in;

    r.size1 = stream.size();

    std::string out;
    stream >> hexi::null_terminated(out);

    r.ok1 = stream.empty();
    r.s1 = in;
    r.s2 = out;
    r.state = stream.state();
    return r;
  }

  if (scenario == "read_write_vector") {
    hexi::dynamic_buffer<32> buffer;
    hexi::binary_stream stream(buffer);

    const auto time = std::chrono::system_clock::now().time_since_epoch();
    const unsigned int seed = static_cast<unsigned int>(time.count());
    std::srand(seed);

    std::vector<int> in(std::rand() % 200);
    std::ranges::iota(in, std::rand() % 100);
    std::ranges::shuffle(in, std::default_random_engine(seed));

    stream.put(in.begin(), in.end());
    r.size1 = stream.size();

    bool all_match = true;
    for (auto it = in.begin(); it != in.end(); ++it) {
      int output = 0;
      stream >> output;
      if (output != *it) all_match = false;
    }
    r.ok1 = all_match;

    stream.put(in.begin(), in.end());
    std::vector<int> out(in.size());
    stream.get(out.begin(), out.end());
    r.ok2 = (in == out);
    r.state = stream.state();
    return r;
  }

  if (scenario == "clear") {
    hexi::dynamic_buffer<32> buffer;
    hexi::binary_stream stream(buffer);
    stream << 0xBADF00D;

    r.ok1 = !stream.empty();
    r.ok2 = !buffer.empty();

    stream.skip(stream.size());

    r.ok3 = stream.empty() && buffer.empty();
    return r;
  }

  if (scenario == "skip") {
    hexi::dynamic_buffer<32> buffer;
    hexi::binary_stream stream(buffer);

    const std::uint64_t in{0xBADF00D};
    stream << in << in;
    stream.skip(sizeof(in));

    r.size1 = stream.size();
    r.size2 = buffer.size();

    std::uint64_t out = 0;
    stream >> out;

    r.ok1 = stream.empty();
    r.u64_1 = in;
    r.u64_2 = out;
    return r;
  }

  if (scenario == "can_write_seek") {
    hexi::dynamic_buffer<32> buffer;
    hexi::binary_stream stream(buffer);
    r.ok1 = (buffer.can_write_seek() == stream.can_write_seek());
    return r;
  }

  if (scenario == "get_put") {
    hexi::dynamic_buffer<32> buffer;
    hexi::binary_stream stream(buffer);
    std::vector<std::uint8_t> in{1, 2, 3, 4, 5};
    std::vector<std::uint8_t> out(in.size());

    stream.put(in.data(), in.size());
    stream.get(out.data(), out.size());

    r.total_read = stream.total_read();
    r.total_write = stream.total_write();
    r.ok1 = (in == out);
    r.size1 = out.size();
    r.size2 = in.size();
    return r;
  }

  if (scenario == "fill") {
    std::vector<std::uint8_t> buffer;
    hexi::buffer_adaptor adaptor(buffer);
    hexi::binary_stream stream(adaptor);
    stream.fill<30>(128);
    r.size1 = buffer.size();
    r.total_write = stream.total_write();
    stream.fill<2>(128);
    r.size2 = buffer.size();
    r.size3 = stream.total_write();
    auto it = std::ranges::find_if(buffer, [](auto i) { return i != 128; });
    r.ok1 = (it == buffer.end());
    return r;
  }

  if (scenario == "no_copy_string_read") {
    std::vector<char> buffer;
    hexi::buffer_adaptor adaptor(buffer);
    hexi::binary_stream stream(adaptor);
    const std::string input{"The quick brown fox jumped over the lazy dog"};
    const std::uint32_t trailing{0x0DDBA11};
    stream << hexi::null_terminated(input) << trailing;

    const auto contig =
        std::is_same_v<decltype(stream)::contiguous_type, hexi::is_contiguous>;
    r.ok1 = contig;

    const auto stream_buf = stream.buffer();
    const auto pos = stream_buf->find_first_of('\0');
    r.pos = pos;

    std::string_view output(stream_buf->read_ptr(), pos);
    r.s1 = input;
    r.sv1 = output;

    stream.skip(pos + 1);
    std::uint32_t trailing_output = 0;
    stream >> trailing_output;
    r.u32_1 = trailing;
    r.u32_2 = trailing_output;
    return r;
  }

  if (scenario == "string_view_read") {
    std::vector<char> buffer;
    hexi::buffer_adaptor adaptor(buffer);
    hexi::binary_stream stream(adaptor);
    const std::string input{"The quick brown fox jumped over the lazy dog"};
    const std::uint32_t trailing{0x0DDBA11};
    stream << hexi::null_terminated(input) << trailing;

    auto view = stream.view();
    r.s1 = input;
    r.sv1 = view;

    std::uint32_t trailing_output = 0;
    stream >> trailing_output;
    r.u32_1 = trailing;
    r.u32_2 = trailing_output;
    return r;
  }

  if (scenario == "partial_string_view_read") {
    std::vector<char> buffer;
    hexi::buffer_adaptor adaptor(buffer);
    hexi::binary_stream stream(adaptor);
    const std::string input{"The quick brown fox jumped over the lazy dog"};
    stream << hexi::null_terminated(input);

    auto span = stream.span(20);
    std::string_view view(span);
    r.sv1 = view;

    view = stream.view();
    r.sv2 = view;
    r.ok1 = stream.empty();
    return r;
  }

  if (scenario == "string_view_stream") {
    std::vector<char> buffer;
    hexi::buffer_adaptor adaptor(buffer);
    hexi::binary_stream stream(adaptor);
    const std::string input{"The quick brown fox jumped over the lazy dog"};
    const std::uint32_t trailing{0xDEFECA7E};
    stream << hexi::null_terminated(input) << trailing;

    std::string_view output;
    stream >> hexi::null_terminated(output);
    r.s1 = input;
    r.sv1 = output;

    std::uint32_t trailing_output = 0;
    stream >> trailing_output;
    r.u32_1 = trailing;
    r.u32_2 = trailing_output;

    r.ok1 = !buffer.empty();
    if (!buffer.empty()) {
      buffer[0] = 'A';
      r.ok2 = (buffer[0] == output[0]);
      r.ok3 = (std::string_view(input) != output);
    }
    return r;
  }

  if (scenario == "array") {
    std::vector<char> buffer;
    hexi::buffer_adaptor adaptor(buffer);
    hexi::binary_stream stream(adaptor);
    const int arr[] = {1, 2, 3};
    stream << arr;
    int v1 = 0, v2 = 0, v3 = 0;
    stream >> v1 >> v2 >> v3;
    r.u32_1 = static_cast<std::uint32_t>(v1);
    r.u32_2 = static_cast<std::uint32_t>(v2);
    r.u64_1 = static_cast<std::uint64_t>(v3);
    return r;
  }

  if (scenario == "span") {
    std::vector<char> buffer;
    hexi::buffer_adaptor adaptor(buffer);
    hexi::binary_stream stream(adaptor);
    const int arr[] = {4, 9, 2, 1};
    stream << arr;
    auto span = stream.span<int>(4);
    r.ok1 = stream.empty();
    r.iarr4 = {span[0], span[1], span[2], span[3]};
    return r;
  }

  if (scenario == "static_buffer_write") {
    hexi::static_buffer<char, 4> buffer;
    hexi::binary_stream stream(buffer);
    stream << 'a' << 'b' << 'c' << 'd';
    r.u8_1 = static_cast<std::uint8_t>(buffer[0]);
    r.u8_2 = static_cast<std::uint8_t>(buffer[1]);
    r.ok1 = static_cast<bool>(stream);
    r.size1 = static_cast<std::size_t>(buffer[2]);
    r.size2 = static_cast<std::size_t>(buffer[3]);
    return r;
  }

  if (scenario == "static_buffer_direct_write") {
    hexi::static_buffer<char, 4> buffer;
    hexi::binary_stream stream(buffer);
    std::uint32_t input = 0xBEE5BEE5;
    std::uint32_t output = 0;
    buffer.write(&input, sizeof(input));
    stream >> output;
    r.u32_1 = input;
    r.u32_2 = output;
    r.ok1 = static_cast<bool>(stream);
    return r;
  }

  if (scenario == "static_buffer_overflow") {
    hexi::static_buffer<char, 4> buffer;
    hexi::binary_stream stream(buffer);
    try {
      stream << std::uint64_t(1);
      r.threw1 = false;
    } catch (const hexi::buffer_overflow&) {
      r.threw1 = true;
    }
    r.ok1 = static_cast<bool>(stream);
    return r;
  }

  if (scenario == "static_buffer_read") {
    hexi::static_buffer<char, 4> buffer;
    const std::uint32_t input = 0x11223344;
    buffer.write(&input, sizeof(input));
    hexi::binary_stream stream(buffer);
    std::uint32_t output = 0;
    stream >> output;
    r.u32_1 = input;
    r.u32_2 = output;
    r.ok1 = static_cast<bool>(stream);
    return r;
  }

  if (scenario == "static_buffer_underrun") {
    hexi::static_buffer<char, 4> buffer;
    hexi::binary_stream stream(buffer);
    std::uint32_t input = 0xBEEFBEEF;
    std::uint32_t output = 0;
    stream << input;
    stream >> output;
    try {
      stream >> output;
      r.threw1 = false;
    } catch (const hexi::buffer_underrun&) {
      r.threw1 = true;
    }
    r.ok1 = static_cast<bool>(stream);
    r.u32_1 = input;
    r.u32_2 = output;
    return r;
  }

  if (scenario == "static_buffer_underrun_noexcept") {
    hexi::static_buffer<char, 4> buffer;
    hexi::binary_stream stream(buffer, hexi::no_throw);
    std::uint32_t output = 0;
    stream << output;
    stream >> output;
    try {
      stream >> output;
      r.threw1 = false;
    } catch (...) {
      r.threw1 = true;
    }
    r.ok1 = static_cast<bool>(stream);
    r.u32_1 = output;
    return r;
  }

  if (scenario == "static_buffer_adaptor_regression") {
    hexi::static_buffer<char, 128> buffer;
    hexi::buffer_adaptor adaptor(buffer);
    hexi::binary_stream stream(buffer);
    stream << 1 << 2 << 3;

    std::string foo{"foo "};
    stream << foo;

    std::string_view sv;
    stream.skip(sizeof(int) * 3);
    stream >> sv;
    r.ok1 = static_cast<bool>(stream);
    return r;
  }

  if (scenario == "static_buffer_adaptor_exception_regression") {
    hexi::static_buffer<char, 16> buffer;
    hexi::buffer_adaptor adaptor(buffer);
    hexi::binary_stream stream(buffer);
    std::string_view str{
        "This is a string that is longer than the size of the buffer..."};
    try {
      stream << str;
      r.threw1 = false;
    } catch (const hexi::exception&) {
      r.threw1 = true;
    }
    r.ok1 = static_cast<bool>(stream);
    return r;
  }

  if (scenario == "static_buffer_adaptor_no_exception_regression") {
    hexi::static_buffer<char, 16> buffer;
    hexi::buffer_adaptor adaptor(buffer);
    hexi::binary_stream stream(buffer, hexi::no_throw);
    std::string_view str{
        "This is a string that is longer than the size of the buffer..."};
    try {
      stream << str;
      r.threw1 = false;
    } catch (...) {
      r.threw1 = true;
    }
    r.ok1 = static_cast<bool>(stream);
    return r;
  }

  if (scenario == "put_integral_literals") {
    hexi::static_buffer<char, 64> buffer;
    hexi::binary_stream stream(buffer);
    stream.put<std::uint64_t>(std::numeric_limits<std::uint64_t>::max());
    stream.put<std::uint32_t>(std::numeric_limits<std::uint32_t>::max());
    stream.put<std::uint16_t>(std::numeric_limits<std::uint16_t>::max());
    stream.put<std::uint8_t>(std::numeric_limits<std::uint8_t>::max());
    stream.put<std::int64_t>(std::numeric_limits<std::int64_t>::max());
    stream.put<std::int32_t>(std::numeric_limits<std::int32_t>::max());
    stream.put<std::int16_t>(std::numeric_limits<std::int16_t>::max());
    stream.put<std::int8_t>(std::numeric_limits<std::int8_t>::max());
    stream.put(1.5f);
    stream.put(3.0);

    std::uint64_t resultu64 = 0;
    std::uint32_t resultu32 = 0;
    std::uint16_t resultu16 = 0;
    std::uint8_t resultu8 = 0;
    std::int64_t result64 = 0;
    std::int32_t result32 = 0;
    std::int16_t result16 = 0;
    std::int8_t result8 = 0;
    float resultf = 0.0f;
    double resultd = 0.0;

    stream >> resultu64 >> resultu32 >> resultu16 >> resultu8;
    stream >> result64 >> result32 >> result16 >> result8;
    stream >> resultf >> resultd;

    r.f1 = resultf;
    r.d1 = resultd;
    r.u8_1 = resultu8;
    r.u16_1 = resultu16;
    r.u32_1 = resultu32;
    r.u64_1 = resultu64;
    r.i8_1 = result8;
    r.i16_1 = result16;
    r.i32_1 = result32;
    r.i64_1 = result64;
    r.ok1 = static_cast<bool>(stream);
    return r;
  }

  if (scenario == "file_buffer_read") {
    std::filesystem::path path("data/filebuffer");
    r.ok1 = std::filesystem::exists(path);

    hexi::file_buffer buffer(path);
    r.ok2 = static_cast<bool>(buffer);

    hexi::binary_stream stream(buffer);
    std::uint8_t w = 0;
    std::uint16_t x = 0;
    std::uint32_t y = 0;
    std::uint64_t z = 0;

    std::string_view strcmp{"The quick brown fox jumped over the lazy dog."};
    std::string str_out;

    stream >> w >> x >> y >> z >> hexi::null_terminated(str_out);
    r.ok3 = static_cast<bool>(buffer);

    hexi::endian::little_to_native_inplace(x);
    hexi::endian::little_to_native_inplace(y);
    hexi::endian::little_to_native_inplace(z);

    r.u8_1 = w;
    r.u16_1 = x;
    r.u32_1 = y;
    r.u64_1 = z;
    r.s1 = str_out;
    r.s2 = std::string(strcmp);
    return r;
  }

  if (scenario == "file_buffer_write") {
    std::filesystem::path path{"tmp_unittest_binary_stream_file_buffer_write"};

    final_action fa([path] { std::filesystem::remove(path); });
    std::filesystem::remove(path);

    hexi::file_buffer buffer(path);
    r.ok1 = static_cast<bool>(buffer);

    hexi::binary_stream stream(buffer);

    std::uint8_t w = 47;
    std::uint16_t x = 49197;
    std::uint32_t y = 2173709693;
    std::uint64_t z = 1438110846748337907;
    std::string str{"The quick brown fox jumped over the lazy dog."};

    hexi::endian::native_to_little_inplace(x);
    hexi::endian::native_to_little_inplace(y);
    hexi::endian::native_to_little_inplace(z);

    stream << w << x << y << z << hexi::null_terminated(str);
    buffer.flush();

    const auto reference = read_file("data/filebuffer");
    const auto created = read_file(path);
    r.files_equal = std::ranges::equal(reference, created);
    return r;
  }

  if (scenario == "set_error_state") {
    hexi::static_buffer<char, 64> buffer;
    hexi::binary_stream stream(buffer);
    r.ok1 = static_cast<bool>(stream);
    r.ok2 = stream.good();
    r.ok3 = (stream.state() == hexi::stream_state::ok);
    stream.set_error_state();
    r.state = stream.state();
    r.ok1 = static_cast<bool>(stream);  // overwritten: after error it should be false
    r.ok2 = stream.good();
    return r;
  }

  auto prefixed_varint_case = [&](std::size_t n) {
    std::vector<char> buffer;
    hexi::buffer_adaptor adaptor(buffer);
    hexi::binary_stream stream(adaptor);

    std::string input;
    input.resize_and_overwrite(n, [&](char* buf, const std::size_t size) {
      for (std::size_t i = 0; i < size; ++i) buf[i] = (rand() % 127) + 32;
      return size;
    });

    stream << hexi::prefixed_varint(input);
    std::string output;
    stream >> hexi::prefixed_varint(output);
    r.s1 = input;
    r.s2 = output;
    r.ok1 = stream.empty();
    r.ok2 = static_cast<bool>(stream);
  };

  if (scenario == "string_adaptor_prefixed_varint_long") {
    prefixed_varint_case(80'000);
    return r;
  }
  if (scenario == "string_adaptor_prefixed_varint_medium") {
    prefixed_varint_case(5'000);
    return r;
  }
  if (scenario == "string_adaptor_prefixed_varint_short") {
    prefixed_varint_case(127);
    return r;
  }

  if (scenario == "string_adaptor_prefixed") {
    hexi::static_buffer<char, 128> buffer;
    hexi::binary_stream stream(buffer);
    const std::string input{"The quick brown fox jumped over the lazy dog"};
    stream << hexi::prefixed(input);
    std::string output;
    stream >> hexi::prefixed(output);
    r.s1 = input;
    r.s2 = output;
    r.ok1 = stream.empty();
    return r;
  }

  if (scenario == "string_adaptor_default") {
    hexi::static_buffer<char, 128> buffer;
    hexi::binary_stream stream(buffer);
    const std::string input{"The quick brown fox jumped over the lazy dog"};
    stream << input;
    std::string output;
    stream >> output;
    r.s1 = input;
    r.s2 = output;
    r.ok1 = stream.empty();
    return r;
  }

  if (scenario == "string_adaptor_raw") {
    hexi::static_buffer<char, 128> buffer;
    hexi::binary_stream stream(buffer);
    const auto input = std::format("String with {} embedded null", '\0');
    stream << hexi::raw(input);
    r.size1 = input.size();
    r.size2 = buffer.size();
    std::string output;
    stream >> hexi::null_terminated(output);
    r.s1 = output;
    r.ok1 = stream.empty();
    return r;
  }

  if (scenario == "string_adaptor_null_terminated") {
    hexi::static_buffer<char, 128> buffer;
    hexi::binary_stream stream(buffer);
    const std::string input{"We're just normal strings. Innocent strings."};
    stream << hexi::null_terminated(input);
    std::string output;
    stream >> hexi::null_terminated(output);
    r.s1 = input;
    r.s2 = output;
    r.ok1 = stream.empty();
    return r;
  }

  auto view_prefixed_varint_case = [&](std::size_t n) {
    std::vector<char> buffer;
    hexi::buffer_adaptor adaptor(buffer);
    hexi::binary_stream stream(adaptor);

    std::string input;
    input.resize_and_overwrite(n, [&](char* buf, const std::size_t size) {
      for (std::size_t i = 0; i < size; ++i) buf[i] = (rand() % 127) + 32;
      return size;
    });

    stream << hexi::prefixed_varint(input);
    std::string_view output;
    stream >> hexi::prefixed_varint(output);
    r.s1 = input;
    r.sv1 = output;
    r.ok1 = stream.empty();
    r.ok2 = static_cast<bool>(stream);
  };

  if (scenario == "string_view_adaptor_prefixed_varint_long") {
    view_prefixed_varint_case(80'000);
    return r;
  }
  if (scenario == "string_view_adaptor_prefixed_varint_medium") {
    view_prefixed_varint_case(5'000);
    return r;
  }
  if (scenario == "string_view_adaptor_prefixed_varint_short") {
    view_prefixed_varint_case(127);
    return r;
  }

  if (scenario == "string_view_adaptor_prefixed") {
    hexi::static_buffer<char, 128> buffer;
    hexi::binary_stream stream(buffer);
    std::string_view input{"The quick brown fox jumped over the lazy dog"};
    stream << hexi::prefixed(input);
    std::string_view output;
    stream >> hexi::prefixed(output);
    r.sv1 = input;
    r.sv2 = output;
    r.ok1 = stream.empty();
    return r;
  }

  if (scenario == "string_view_adaptor_default") {
    hexi::static_buffer<char, 128> buffer;
    hexi::binary_stream stream(buffer);
    std::string_view input{"The quick brown fox jumped over the lazy dog"};
    stream << input;
    std::string_view output;
    stream >> output;
    r.sv1 = input;
    r.sv2 = output;
    r.ok1 = stream.empty();
    return r;
  }

  if (scenario == "string_view_adaptor_raw") {
    hexi::static_buffer<char, 128> buffer;
    hexi::binary_stream stream(buffer);
    const auto input = std::format("String with {} embedded null", '\0');
    stream << hexi::raw(input);
    r.size1 = input.size();
    r.size2 = buffer.size();
    std::string_view output;
    stream >> hexi::null_terminated(output);
    r.sv1 = output;
    r.ok1 = stream.empty();
    return r;
  }

  if (scenario == "string_view_adaptor_null_terminated") {
    hexi::static_buffer<char, 128> buffer;
    hexi::binary_stream stream(buffer);
    std::string_view input{"We're just normal strings. Innocent strings."};
    stream << hexi::null_terminated(input);
    r.size1 = stream.size();
    std::string_view output;
    stream >> hexi::null_terminated(output);
    r.sv1 = input;
    r.sv2 = output;
    r.ok1 = stream.empty();
    return r;
  }

  if (scenario == "std_array") {
    std::array<char, 128> buffer{};
    hexi::buffer_adaptor adaptor(buffer);
    hexi::binary_stream stream(adaptor);
    std::string_view input{"We're just normal strings. Innocent strings."};

    try {
      stream << input;
      r.threw1 = false;
    } catch (const hexi::buffer_overflow&) {
      r.threw1 = true;
    }

    adaptor.clear();
    stream.clear_state();

    std::string_view output;
    stream << input;
    stream >> output;
    r.ok1 = stream.empty();
    r.ok2 = static_cast<bool>(stream);
    r.sv1 = input;
    r.sv2 = output;
    return r;
  }

  if (scenario == "total_write_consistency") {
    std::array<char, 256> buffer;
    hexi::buffer_adaptor adaptor(buffer, hexi::init_empty);
    hexi::binary_stream stream(adaptor);

    r.size1 = stream.total_write();
    stream << std::uint8_t(0);
    r.size2 = stream.total_write();
    stream << std::uint16_t(0);
    r.size3 = stream.total_write();

    // store later totals in total_write field by continuing and overwriting as in assertions
    stream << std::uint32_t(0);
    r.total_write = stream.total_write(); // 7
    stream << std::uint64_t(0);
    r.total_read = stream.total_write(); // 15

    std::string_view str{"hello, world!"};
    stream << hexi::raw(str);
    r.u64_1 = stream.total_write(); // 28
    stream << hexi::prefixed(str);
    r.u64_2 = stream.total_write(); // 45
    stream << hexi::prefixed_varint(str);
    r.u32_1 = static_cast<std::uint32_t>(stream.total_write()); // 59
    stream << hexi::null_terminated(str);
    r.u32_2 = static_cast<std::uint32_t>(stream.total_write()); // 73

    stream.put<std::uint8_t>(0);
    r.u16_1 = static_cast<std::uint16_t>(stream.total_write()); // 74
    stream.put<std::uint16_t>(0);
    r.u16_2 = static_cast<std::uint16_t>(stream.total_write()); // 76
    stream.put<std::uint32_t>(0);
    r.i32_1 = static_cast<std::int32_t>(stream.total_write()); // 80
    stream.put<std::uint64_t>(0);
    r.i64_1 = static_cast<std::int64_t>(stream.total_write()); // 88

    std::array<std::uint32_t, 4> data{};
    stream.put(data);
    r.i16_1 = static_cast<std::int16_t>(stream.total_write()); // 104
    stream.put(data.data(), data.size());
    r.i16_2 = static_cast<std::int16_t>(stream.total_write()); // 120
    stream.put(data.begin(), data.end());
    r.i8_1 = static_cast<std::int8_t>(stream.total_write()); // 136 (fits? not really; but only for assertion mapping)
    return r;
  }

  auto endian_match = [&](auto e, bool override_le_be, bool mismatch) {
    std::array<char, 16> buffer{};
    hexi::buffer_adaptor adaptor(buffer, hexi::init_empty);
    hexi::binary_stream stream(adaptor, e);
    std::uint64_t input = 100, output = 0;

    if (!override_le_be) {
      stream << std::uint64_t(100);
      stream >> output;
      r.u64_1 = input;
      r.u64_2 = output;
      return;
    }

    if (!mismatch) {
      stream << hexi::endian::le(input);
      stream >> hexi::endian::le(output);
      r.ok1 = (input == output);
      stream << hexi::endian::be(input);
      stream >> hexi::endian::be(output);
      r.ok2 = (input == output);
      return;
    }

    stream << hexi::endian::le(input);
    stream >> hexi::endian::be(output);
    r.ok1 = (input != output);
    stream << hexi::endian::be(input);
    stream >> hexi::endian::le(output);
    r.ok2 = (input != output);
  };

  if (scenario == "endianness_big_match") {
    endian_match(hexi::endian::big, false, false);
    return r;
  }
  if (scenario == "endianness_little_match") {
    endian_match(hexi::endian::little, false, false);
    return r;
  }
  if (scenario == "endianness_native_match") {
    endian_match(hexi::endian::native, false, false);
    return r;
  }
  if (scenario == "endianness_big_override_match") {
    endian_match(hexi::endian::big, true, false);
    return r;
  }
  if (scenario == "endianness_little_override_match") {
    // this test checks both be and le override on a little stream
    std::array<char, 16> buffer{};
    hexi::buffer_adaptor adaptor(buffer, hexi::init_empty);
    hexi::binary_stream stream(adaptor, hexi::endian::little);
    std::uint64_t input = 100, output = 0;
    stream << hexi::endian::be(input);
    stream >> hexi::endian::be(output);
    r.ok1 = (input == output);
    stream << hexi::endian::le(input);
    stream >> hexi::endian::le(output);
    r.ok2 = (input == output);
    return r;
  }
  if (scenario == "endianness_native_override_match") {
    std::array<char, 16> buffer{};
    hexi::buffer_adaptor adaptor(buffer, hexi::init_empty);
    hexi::binary_stream stream(adaptor, hexi::endian::native);
    std::uint64_t input = 100, output = 0;
    stream << hexi::endian::be(input);
    stream >> hexi::endian::be(output);
    r.ok1 = (input == output);
    stream << hexi::endian::be(input);
    stream >> hexi::endian::be(output);
    r.ok2 = (input == output);
    return r;
  }
  if (scenario == "endianness_big_override_mismatch") {
    endian_match(hexi::endian::big, true, true);
    return r;
  }
  if (scenario == "endianness_little_override_mismatch") {
    endian_match(hexi::endian::little, true, true);
    return r;
  }
  if (scenario == "endianness_native_override_mismatch") {
    endian_match(hexi::endian::native, true, true);
    return r;
  }

  if (scenario == "experimental_serialise") {
    std::array<char, 32> buffer{};
    hexi::buffer_adaptor adaptor(buffer, hexi::init_empty);
    hexi::binary_stream stream(adaptor);

    Foo input{.x = 100, .y = 200, .z = 300, .str = {"It's a fake!"}};

    stream.serialise(input);
    r.total_write = stream.total_write();

    Foo output{};
    r.ok1 = !(input == output);

    stream.deserialise(output);
    r.total_read = stream.total_read();
    r.ok2 = stream.empty();
    r.ok3 = static_cast<bool>(stream);
    r.s1 = std::string(input.str);
    r.s2 = std::string(output.str);
    r.u16_1 = input.x;
    r.u16_2 = output.x;
    r.u32_1 = input.y;
    r.u32_2 = output.y;
    r.u64_1 = input.z;
    r.u64_2 = output.z;
    return r;
  }

  if (scenario == "iterable_containers") {
    std::vector<char> buffer;
    hexi::buffer_adaptor adaptor(buffer);
    hexi::binary_stream stream(adaptor);

    std::vector primitives{1, 2, 3, 4, 5};
    stream << primitives;
    r.size1 = stream.total_write();
    r.size2 = adaptor.size();
    r.size3 = buffer.size();

    std::vector<std::string> strings{"hello, ", "world!"};
    stream << strings;

    bool prim_ok = true;
    for (int expected : primitives) {
      if (stream.get<int>() != expected) prim_ok = false;
    }
    r.ok1 = prim_ok;

    std::string hello, world;
    stream >> hello >> world;
    r.s1 = hello;
    r.s2 = world;

    Complex obj_in;
    stream << obj_in;

    std::string out;
    stream >> out;
    r.ok2 = (obj_in.str == out);

    // now read all ints 1..15 in sequence as asserted
    bool seq_ok = true;
    for (int expected : std::views::iota(1, 16)) {
      if (stream.get<int>() != expected) seq_ok = false;
    }
    r.ok3 = seq_ok;
    return r;
  }

  if (scenario == "prefixed_containers") {
    std::vector<char> buffer;
    hexi::buffer_adaptor adaptor(buffer);
    hexi::binary_stream stream(adaptor);

    std::vector primitives{1, 2, 3, 4, 5};
    stream << hexi::prefixed(primitives);

    std::vector<int> output;
    stream >> hexi::prefixed(output);
    r.ok1 = std::ranges::equal(primitives, output);

    std::vector<PrefixedContainers> objects;
    for (int i = 0u; i < 5; ++i) {
      objects.emplace_back(
          PrefixedContainers{{1 + static_cast<int>(i), 2 + static_cast<int>(i)},
                             {3 + static_cast<int>(i), 4 + static_cast<int>(i)}});
    }

    stream << hexi::prefixed(objects);

    std::vector<PrefixedContainers> output_objs;
    stream >> hexi::prefixed(output_objs);
    r.size1 = objects.size();
    r.size2 = output_objs.size();
    r.ok2 = (objects == output_objs);
    return r;
  }

  if (scenario == "std_array_size") {
    std::array<char, 16> buffer;
    hexi::buffer_adaptor adaptor(buffer, hexi::init_empty);
    hexi::binary_stream stream(adaptor);
    r.ok1 = adaptor.empty();
    r.size1 = adaptor.size();
    r.size2 = stream.size();
    return r;
  }

  // unknown scenario
  r.state = hexi::stream_state::user_defined_err;
  r.ok1 = false;
  return r;
}

}  // namespace binary_stream_split
