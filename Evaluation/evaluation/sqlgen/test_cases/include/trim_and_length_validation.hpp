#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace trim_and_length_validation {

struct UserProfile {
  sqlgen::PrimaryKey<int> user_id;
  std::string name;
  std::string email;
};

struct ValidatedProfile {
  sqlgen::PrimaryKey<int> user_id;
  std::string trimmed_name;
  std::string trimmed_email;
  int name_length;
  int email_length;
};

/**
 * This function demonstrates how to trim whitespace from string columns and validate their lengths using sqlgen read API.
 * Returns: std::vector<ValidatedProfile>, where each struct contains the user_id, trimmed_name, trimmed_email, name_length, and email_length.
 */
std::vector<ValidatedProfile> trim_and_length_validation() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn_res = sqlite::connect("test_db.sqlite");
  if (!conn_res) return {};
  auto conn = conn_res.value();

  create_table<UserProfile>(conn);

  const auto query =
      select_from<UserProfile>(
          col<"user_id"> | as<"user_id">, trim(col<"name">) | as<"trimmed_name">,
          trim(col<"email">) | as<"trimmed_email">,
          length(trim(col<"name">)) | as<"name_length">,
          length(trim(col<"email">)) | as<"email_length">) |
      to<std::vector<ValidatedProfile>>;

  return query(conn).value();
}

}  // namespace trim_and_length_validation

