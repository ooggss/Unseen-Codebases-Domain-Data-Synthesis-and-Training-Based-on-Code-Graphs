#include <gtest/gtest.h>
#include <sqlgen/sqlite.hpp>
#include "analyze_social_network.hpp"

using namespace analyze_social_network;

TEST(sqlite, AnalyzeSocialNetwork) {
  using namespace sqlgen;
  using namespace sqlgen::literals;
  using Timestamp = sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S">;

  std::vector<User> users = {
      {1, "Alice"},
      {2, "Bob"},
      {3, "Charlie"},
      {4, "David"}
  };

  std::vector<Friendship> friendships = {
      {1, 2, Timestamp("2023-01-01 10:00:00")}, // Alice - Bob
      {2, 3, Timestamp("2023-01-02 11:00:00")}, // Bob - Charlie
      {1, 4, Timestamp("2023-01-03 12:00:00")}  // Alice - David
  };
  auto conn = sqlite::connect("test_db.sqlite").value();
  drop<User>(conn);
  drop<Friendship>(conn);
  create_table<User>(conn);
  create_table<Friendship>(conn);
  insert(conn, users);
  insert(conn, friendships);

  auto connections = analyze_social_network_impl();

  ASSERT_EQ(connections.size(), 3);

  // Helper to check if a connection exists
  auto has_connection = [&](const std::string& u1, const std::string& u2) {
    for (const auto& conn : connections) {
      if ((conn.user1_name == u1 && conn.user2_name == u2) ||
          (conn.user1_name == u2 && conn.user2_name == u1)) {
        return true;
      }
    }
    return false;
  };

  EXPECT_TRUE(has_connection("Alice", "Bob"));
  EXPECT_TRUE(has_connection("Bob", "Charlie"));
  EXPECT_TRUE(has_connection("Alice", "David"));
  EXPECT_FALSE(has_connection("Bob", "David"));
}
