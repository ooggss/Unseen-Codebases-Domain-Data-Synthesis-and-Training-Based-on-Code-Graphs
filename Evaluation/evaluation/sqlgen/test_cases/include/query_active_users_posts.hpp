#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace query_active_users_posts {

struct User {
  sqlgen::PrimaryKey<int> user_id;
  std::string username;
};

struct Post {
  sqlgen::PrimaryKey<int> post_id;
  int user_id;
  sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S"> created_at;
};

struct ActiveUser {
  static constexpr const char* tablename = "ActiveUserView";
  static constexpr bool is_view = true;
  sqlgen::PrimaryKey<int> user_id;
  std::string username;
};

/**
 * Description: This function returns a list of active users who have posted within the last year.
 * Returns: std::vector<ActiveUser>.
 */
std::vector<ActiveUser> query_active_users_posts() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn = sqlite::connect("test_db.sqlite");
  if (!conn) return {};
  create_table<User>(conn);
  create_table<Post>(conn);

  const auto query = 
      select_from<User, "t1">(
          "user_id"_t1 | as<"user_id">,
          "username"_t1 | as<"username">) |
      inner_join<Post, "t2">("user_id"_t1 == "user_id"_t2) |
      where("created_at"_t2 >= sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S">("2025-12-01 00:00:00") &&
            "created_at"_t2 <= sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S">("2025-12-31 23:59:59")) |
      group_by("user_id"_t1, "username"_t1);

  const auto create_view = create_as<ActiveUser>(query) | if_not_exists;
  create_view(conn);

  return sqlgen::read<std::vector<ActiveUser>>(conn).value();
}

}  // namespace query_active_users_posts

