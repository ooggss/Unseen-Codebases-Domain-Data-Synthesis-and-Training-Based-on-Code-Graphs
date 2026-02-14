
#include <gtest/gtest.h>

#include <hexi/binary_stream.h>
#include <hexi/endian.h>

#include <limits>
#include <string>
#include <string_view>

// In a real project, include via a header. For this split output, include the .cpp directly.
#include "binary_stream_function_implementation_0.hpp"

using binary_stream_split::Result;
using binary_stream_split::run_binary_stream_scenario;

TEST(binary_stream, message_read_limit) {
  const auto r = run_binary_stream_scenario("message_read_limit");
  ASSERT_EQ(r.size1, 14u);
  ASSERT_TRUE(r.ok1) << "Failed to read packet back from stream";
  ASSERT_TRUE(r.threw1) << "Message boundary was not respected";
  ASSERT_EQ(r.state, hexi::stream_state::read_limit_err) << "Unexpected stream state";
}

TEST(binary_stream, buffer_limit) {
  const auto r = run_binary_stream_scenario("buffer_limit");
  ASSERT_TRUE(r.ok1) << "Failed to read packet back from stream";
  ASSERT_TRUE(r.threw1) << "Message boundary was not respected";
  ASSERT_EQ(r.state, hexi::stream_state::buff_limit_err) << "Unexpected stream state";
}

TEST(binary_stream, read_write_ints) {
  const auto r = run_binary_stream_scenario("read_write_ints");
  ASSERT_EQ(r.size1, sizeof(std::uint16_t));
  ASSERT_EQ(r.size1, r.size2);
  ASSERT_EQ(r.u16_1, r.u16_2);
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
  ASSERT_EQ(r.state, hexi::stream_state::ok) << "Unexpected stream state";
}

TEST(binary_stream, read_write_std_string) {
  const auto r = run_binary_stream_scenario("read_write_std_string");
  ASSERT_EQ(r.size1, r.s1.size() + 1);
  ASSERT_TRUE(r.ok1);
  ASSERT_EQ(r.s1, r.s2);
  ASSERT_EQ(r.state, hexi::stream_state::ok) << "Unexpected stream state";
}

TEST(binary_stream, read_write_c_string) {
  const auto r = run_binary_stream_scenario("read_write_c_string");
  ASSERT_EQ(r.size1, r.s1.size() + 1);
  ASSERT_TRUE(r.ok1);
  ASSERT_EQ(r.s1, r.s2);
  ASSERT_EQ(r.state, hexi::stream_state::ok) << "Unexpected stream state";
}

TEST(binary_stream, read_write_vector) {
  const auto r = run_binary_stream_scenario("read_write_vector");
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
  ASSERT_EQ(r.state, hexi::stream_state::ok) << "Unexpected stream state";
}

TEST(binary_stream, clear) {
  const auto r = run_binary_stream_scenario("clear");
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
  ASSERT_TRUE(r.ok3);
}

TEST(binary_stream, skip) {
  const auto r = run_binary_stream_scenario("skip");
  ASSERT_EQ(r.size1, sizeof(std::uint64_t));
  ASSERT_EQ(r.size1, r.size2);
  ASSERT_TRUE(r.ok1);
  ASSERT_EQ(r.u64_1, r.u64_2);
}

TEST(binary_stream, can_write_seek) {
  const auto r = run_binary_stream_scenario("can_write_seek");
  ASSERT_TRUE(r.ok1);
}

TEST(binary_stream, get_put) {
  const auto r = run_binary_stream_scenario("get_put");
  ASSERT_EQ(r.total_read, r.size1);
  ASSERT_EQ(r.total_write, r.size2);
  ASSERT_TRUE(r.ok1);
}

TEST(binary_stream, fill) {
  const auto r = run_binary_stream_scenario("fill");
  ASSERT_EQ(r.size1, 30u);
  ASSERT_EQ(r.total_write, 30u);
  ASSERT_EQ(r.size2, 32u);
  ASSERT_EQ(r.size3, 32u);
  ASSERT_TRUE(r.ok1);
}

TEST(binary_stream, no_copy_string_read) {
  const auto r = run_binary_stream_scenario("no_copy_string_read");
  ASSERT_TRUE(r.ok1);
  ASSERT_NE(r.pos, std::string::npos);
  ASSERT_EQ(r.s1, r.sv1);
  ASSERT_EQ(r.u32_1, r.u32_2);
}

TEST(binary_stream, string_view_read) {
  const auto r = run_binary_stream_scenario("string_view_read");
  ASSERT_EQ(r.s1, r.sv1);
  ASSERT_EQ(r.u32_1, r.u32_2);
}

TEST(binary_stream, partial_string_view_read) {
  const auto r = run_binary_stream_scenario("partial_string_view_read");
  ASSERT_EQ(std::string_view("The quick brown fox "), r.sv1);
  ASSERT_EQ(std::string_view("jumped over the lazy dog"), r.sv2);
  ASSERT_TRUE(r.ok1);
}

TEST(binary_stream, string_view_stream) {
  const auto r = run_binary_stream_scenario("string_view_stream");
  ASSERT_EQ(r.s1, r.sv1);
  ASSERT_EQ(r.u32_1, r.u32_2);
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
  ASSERT_TRUE(r.ok3);
}

TEST(binary_stream, array) {
  const auto r = run_binary_stream_scenario("array");
  ASSERT_EQ(static_cast<int>(r.u32_1), 1);
  ASSERT_EQ(static_cast<int>(r.u32_2), 2);
  ASSERT_EQ(static_cast<int>(r.u64_1), 3);
}

TEST(binary_stream, span) {
  const auto r = run_binary_stream_scenario("span");
  ASSERT_TRUE(r.ok1);
  ASSERT_EQ(r.iarr4[0], 4);
  ASSERT_EQ(r.iarr4[1], 9);
  ASSERT_EQ(r.iarr4[2], 2);
  ASSERT_EQ(r.iarr4[3], 1);
}

TEST(binary_stream, static_buffer_write) {
  const auto r = run_binary_stream_scenario("static_buffer_write");
  ASSERT_EQ(static_cast<char>(r.u8_1), 'a');
  ASSERT_EQ(static_cast<char>(r.u8_2), 'b');
  ASSERT_EQ(static_cast<char>(r.size1), 'c');
  ASSERT_EQ(static_cast<char>(r.size2), 'd');
  ASSERT_TRUE(r.ok1);
}

TEST(binary_stream, static_buffer_direct_write) {
  const auto r = run_binary_stream_scenario("static_buffer_direct_write");
  ASSERT_EQ(r.u32_1, r.u32_2);
  ASSERT_TRUE(r.ok1);
}

TEST(binary_stream, static_buffer_overflow) {
  const auto r = run_binary_stream_scenario("static_buffer_overflow");
  ASSERT_TRUE(r.threw1);
  ASSERT_FALSE(r.ok1);
}

TEST(binary_stream, static_buffer_read) {
  const auto r = run_binary_stream_scenario("static_buffer_read");
  ASSERT_EQ(r.u32_1, r.u32_2);
  ASSERT_TRUE(r.ok1);
}

TEST(binary_stream, static_buffer_underrun) {
  const auto r = run_binary_stream_scenario("static_buffer_underrun");
  ASSERT_TRUE(r.threw1);
  ASSERT_FALSE(r.ok1);
  ASSERT_EQ(r.u32_1, r.u32_2);
}

TEST(binary_stream, static_buffer_underrun_noexcept) {
  const auto r = run_binary_stream_scenario("static_buffer_underrun_noexcept");
  ASSERT_FALSE(r.threw1);
  ASSERT_FALSE(r.ok1);
  ASSERT_EQ(r.u32_1, 0u);
}

TEST(binary_stream, static_buffer_adaptor_regression) {
  const auto r = run_binary_stream_scenario("static_buffer_adaptor_regression");
  ASSERT_TRUE(r.ok1);
}

TEST(binary_stream, static_buffer_adaptor_exception_regression) {
  const auto r = run_binary_stream_scenario("static_buffer_adaptor_exception_regression");
  ASSERT_TRUE(r.threw1);
  ASSERT_FALSE(r.ok1);
}

TEST(binary_stream, static_buffer_adaptor_no_exception_regression) {
  const auto r = run_binary_stream_scenario("static_buffer_adaptor_no_exception_regression");
  ASSERT_FALSE(r.threw1);
  ASSERT_FALSE(r.ok1);
}

TEST(binary_stream, put_integral_literals) {
  const auto r = run_binary_stream_scenario("put_integral_literals");
  ASSERT_FLOAT_EQ(1.5f, r.f1);
  ASSERT_DOUBLE_EQ(3.0, r.d1);
  ASSERT_EQ(r.u8_1, std::numeric_limits<std::uint8_t>::max());
  ASSERT_EQ(r.u16_1, std::numeric_limits<std::uint16_t>::max());
  ASSERT_EQ(r.u32_1, std::numeric_limits<std::uint32_t>::max());
  ASSERT_EQ(r.u64_1, std::numeric_limits<std::uint64_t>::max());
  ASSERT_EQ(r.i8_1, std::numeric_limits<std::int8_t>::max());
  ASSERT_EQ(r.i16_1, std::numeric_limits<std::int16_t>::max());
  ASSERT_EQ(r.i32_1, std::numeric_limits<std::int32_t>::max());
  ASSERT_EQ(r.i64_1, std::numeric_limits<std::int64_t>::max());
  ASSERT_TRUE(r.ok1);
}

TEST(binary_stream, file_buffer_read) {
  const auto r = run_binary_stream_scenario("file_buffer_read");
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2) << "File open failed";
  ASSERT_TRUE(r.ok3) << "File read error occurred";
  ASSERT_EQ(r.u8_1, 47) << "Wrong uint8 value";
  ASSERT_EQ(r.u16_1, 49197) << "Wrong uint16 value";
  ASSERT_EQ(r.u32_1, 2173709693u) << "Wrong uint32 value";
  ASSERT_EQ(r.u64_1, 1438110846748337907ull) << "Wrong uint64 value";
  ASSERT_EQ(r.s1, r.s2);
}

TEST(binary_stream, file_buffer_write) {
  const auto r = run_binary_stream_scenario("file_buffer_write");
  ASSERT_TRUE(r.ok1) << "File open failed";
  ASSERT_TRUE(r.files_equal);
}

TEST(binary_stream, set_error_state) {
  const auto r = run_binary_stream_scenario("set_error_state");
  ASSERT_FALSE(r.ok1);
  ASSERT_FALSE(r.ok2);
  ASSERT_TRUE(r.state == hexi::stream_state::user_defined_err);
}

TEST(binary_stream, string_adaptor_prefixed_varint_long) {
  const auto r = run_binary_stream_scenario("string_adaptor_prefixed_varint_long");
  ASSERT_EQ(r.s1, r.s2);
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
}

TEST(binary_stream, string_adaptor_prefixed_varint_medium) {
  const auto r = run_binary_stream_scenario("string_adaptor_prefixed_varint_medium");
  ASSERT_EQ(r.s1, r.s2);
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
}

TEST(binary_stream, string_adaptor_prefixed_varint_short) {
  const auto r = run_binary_stream_scenario("string_adaptor_prefixed_varint_short");
  ASSERT_EQ(r.s1, r.s2);
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
}

TEST(binary_stream, string_adaptor_prefixed) {
  const auto r = run_binary_stream_scenario("string_adaptor_prefixed");
  ASSERT_EQ(r.s1, r.s2);
  ASSERT_TRUE(r.ok1);
}

TEST(binary_stream, string_adaptor_default) {
  const auto r = run_binary_stream_scenario("string_adaptor_default");
  ASSERT_EQ(r.s1, r.s2);
  ASSERT_TRUE(r.ok1);
}

TEST(binary_stream, string_adaptor_raw) {
  const auto r = run_binary_stream_scenario("string_adaptor_raw");
  ASSERT_EQ(r.size1, r.size2);
  ASSERT_EQ(r.s1, "String with ");
  ASSERT_FALSE(r.ok1);
}

TEST(binary_stream, string_adaptor_null_terminated) {
  const auto r = run_binary_stream_scenario("string_adaptor_null_terminated");
  ASSERT_EQ(r.s1, r.s2);
  ASSERT_TRUE(r.ok1);
}

TEST(binary_stream, string_view_adaptor_prefixed_varint_long) {
  const auto r = run_binary_stream_scenario("string_view_adaptor_prefixed_varint_long");
  ASSERT_EQ(r.s1, r.sv1);
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
}

TEST(binary_stream, string_view_adaptor_prefixed_varint_medium) {
  const auto r = run_binary_stream_scenario("string_view_adaptor_prefixed_varint_medium");
  ASSERT_EQ(r.s1, r.sv1);
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
}

TEST(binary_stream, string_view_adaptor_prefixed_varint_short) {
  const auto r = run_binary_stream_scenario("string_view_adaptor_prefixed_varint_short");
  ASSERT_EQ(r.s1, r.sv1);
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
}

TEST(binary_stream, string_view_adaptor_prefixed) {
  const auto r = run_binary_stream_scenario("string_view_adaptor_prefixed");
  ASSERT_EQ(r.sv1, r.sv2);
  ASSERT_TRUE(r.ok1);
}

TEST(binary_stream, string_view_adaptor_default) {
  const auto r = run_binary_stream_scenario("string_view_adaptor_default");
  ASSERT_EQ(r.sv1, r.sv2);
  ASSERT_TRUE(r.ok1);
}

TEST(binary_stream, string_view_adaptor_raw) {
  const auto r = run_binary_stream_scenario("string_view_adaptor_raw");
  ASSERT_EQ(r.size1, r.size2);
  ASSERT_EQ(r.sv1, "String with ");
  ASSERT_FALSE(r.ok1);
}

TEST(binary_stream, string_view_adaptor_null_terminated) {
  const auto r = run_binary_stream_scenario("string_view_adaptor_null_terminated");
  ASSERT_EQ(r.size1, r.sv1.size() + 1);
  ASSERT_EQ(r.sv1, r.sv2);
  ASSERT_TRUE(r.ok1);
}

TEST(binary_stream, std_array) {
  const auto r = run_binary_stream_scenario("std_array");
  ASSERT_TRUE(r.threw1);
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
  ASSERT_EQ(r.sv1, r.sv2);
}

TEST(binary_stream, total_write_consistency) {
  const auto r = run_binary_stream_scenario("total_write_consistency");

  ASSERT_EQ(r.size1, 0u);
  ASSERT_EQ(r.size2, 1u);
  ASSERT_EQ(r.size3, 3u);
  ASSERT_EQ(r.total_write, 7u);
  ASSERT_EQ(r.total_read, 15u);

  ASSERT_EQ(r.u64_1, 28u);
  ASSERT_EQ(r.u64_2, 45u);
  ASSERT_EQ(r.u32_1, 59u);
  ASSERT_EQ(r.u32_2, 73u);

  ASSERT_EQ(r.u16_1, 74u);
  ASSERT_EQ(r.u16_2, 76u);
  ASSERT_EQ(r.i32_1, 80);
  ASSERT_EQ(r.i64_1, 88);

  ASSERT_EQ(r.i16_1, 104);
  ASSERT_EQ(r.i16_2, 120);
  ASSERT_EQ(static_cast<unsigned char>(r.i8_1), static_cast<unsigned char>(136));
}

TEST(binary_stream, endianness_big_match) {
  const auto r = run_binary_stream_scenario("endianness_big_match");
  ASSERT_EQ(r.u64_1, r.u64_2);
}

TEST(binary_stream, endianness_little_match) {
  const auto r = run_binary_stream_scenario("endianness_little_match");
  ASSERT_EQ(r.u64_1, r.u64_2);
}

TEST(binary_stream, endianness_native_match) {
  const auto r = run_binary_stream_scenario("endianness_native_match");
  ASSERT_EQ(r.u64_1, r.u64_2);
}

TEST(binary_stream, endianness_big_override_match) {
  const auto r = run_binary_stream_scenario("endianness_big_override_match");
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
}

TEST(binary_stream, endianness_little_override_match) {
  const auto r = run_binary_stream_scenario("endianness_little_override_match");
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
}

TEST(binary_stream, endianness_native_override_match) {
  const auto r = run_binary_stream_scenario("endianness_native_override_match");
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
}

TEST(binary_stream, endianness_big_override_mismatch) {
  const auto r = run_binary_stream_scenario("endianness_big_override_mismatch");
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
}

TEST(binary_stream, endianness_little_override_mismatch) {
  const auto r = run_binary_stream_scenario("endianness_little_override_mismatch");
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
}

TEST(binary_stream, endianness_native_override_mismatch) {
  const auto r = run_binary_stream_scenario("endianness_native_override_mismatch");
  ASSERT_TRUE(r.ok1);
  ASSERT_TRUE(r.ok2);
}

TEST(binary_stream, experimental_serialise) {
  const auto r = run_binary_stream_scenario("experimental_serialise");
  ASSERT_EQ(r.total_write, 29u);
  ASSERT_TRUE(r.ok1);
  ASSERT_EQ(r.total_read, 29u);
  ASSERT_TRUE(r.ok2);
  ASSERT_TRUE(r.ok3);

  ASSERT_EQ(r.u16_1, r.u16_2);
  ASSERT_EQ(r.u32_1, r.u32_2);
  ASSERT_EQ(r.u64_1, r.u64_2);
  ASSERT_EQ(r.s1, r.s2);
}

TEST(binary_stream, iterable_containers) {
  const auto r = run_binary_stream_scenario("iterable_containers");
  ASSERT_EQ(r.size1, 5u * sizeof(int));
  ASSERT_EQ(r.size2, 5u * sizeof(int));
  ASSERT_EQ(r.size3, 5u * sizeof(int));

  ASSERT_TRUE(r.ok1);

  ASSERT_EQ(r.s1, "hello, ");
  ASSERT_EQ(r.s2, "world!");

  ASSERT_TRUE(r.ok2);
  ASSERT_TRUE(r.ok3);
}

TEST(binary_stream, prefixed_containers) {
  const auto r = run_binary_stream_scenario("prefixed_containers");
  ASSERT_TRUE(r.ok1);
  EXPECT_EQ(r.size1, r.size2);
  ASSERT_TRUE(r.ok2);
}

TEST(binary_stream, std_array_size) {
  const auto r = run_binary_stream_scenario("std_array_size");
  ASSERT_TRUE(r.ok1);
  ASSERT_EQ(r.size1, 0u);
  ASSERT_EQ(r.size2, 0u);
}
