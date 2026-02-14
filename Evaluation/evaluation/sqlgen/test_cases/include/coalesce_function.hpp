#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <string>
#include <optional>

namespace coalesce_function {

struct Profile {
  sqlgen::PrimaryKey<int> id;
  std::optional<std::string> nickname;
};

struct NicknameResult {
  std::string display_name;
};

/**
 * This function demonstrates COALESCE usage.
 * Returns: vector<NicknameResult>
 */
inline std::vector<NicknameResult> coalesce_function() {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto conn = sqlite::connect("test_db.sqlite").value();
    auto query = select_from<Profile>(
        coalesce("nickname"_c, "Anonymous").as<"display_name">()
        // "nickname"_c
    ) | to<std::vector<NicknameResult>>;
    return query(conn).value();
}

}  // namespace coalesce_function