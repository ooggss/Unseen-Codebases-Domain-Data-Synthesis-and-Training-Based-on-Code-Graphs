#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace replace_text_in_notes {

struct Note {
  sqlgen::PrimaryKey<int> note_id;
  std::string content;
};

struct UpdatedNote {
  sqlgen::PrimaryKey<int> note_id;
  std::string updated_content;
};

/**
 * This function demonstrates how to replace text in notes using sqlgen update API.
 * It replaces all occurrences of "foo" with "bar" in the content column of the Note table.
 * Returns: std::vector<UpdatedNote>.
 */
std::vector<UpdatedNote> replace_text_in_notes() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn_res = sqlite::connect("test_db.sqlite");
  if (!conn_res) return {};
  auto conn = conn_res.value();

  const auto query =
      select_from<Note>(col<"note_id"> | as<"note_id">,
                        replace(col<"content">, "foo", "bar") | as<"updated_content">) |
      to<std::vector<UpdatedNote>>;
  return query(conn).value();
}

}  // namespace replace_text_in_notes

