#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>
#include <optional>

namespace analyze_social_network {

struct User {
  sqlgen::PrimaryKey<int> user_id;
  std::string username;
};

struct Friendship {
  int user1_id;
  int user2_id;
  sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S"> created_at;
};

struct FriendConnection {
  std::string user1_name;
  std::string user2_name;
};

/**
 * Analyze who and whom are friends in the social network.
 * Returns: std::vector<FriendConnection>.
 */
std::vector<FriendConnection> analyze_social_network_impl() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn = sqlite::connect("test_db.sqlite").value();

  // Find all pairs of friends
  const auto query = (select_from<Friendship, "f">(
          col<"username", "u1">.as<"user1_name">(), 
          col<"username", "u2">.as<"user2_name">()) |
      inner_join<User, "u1">(col<"user1_id", "f"> == col<"user_id", "u1">) |
      inner_join<User, "u2">(col<"user2_id", "f"> == col<"user_id", "u2">) |
      to<std::vector<FriendConnection>>)(conn);

  return query.value();
}

}  // namespace analyze_social_network
