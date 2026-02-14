#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <string>

namespace create_index_basic {

struct Book {
  sqlgen::PrimaryKey<int> id;
  std::string title;
};

/**
 * This function returns a SQL string to create an index named `idx_book_title` on the `title` column of `Book`.
 */
inline std::string create_index_basic() {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto query = sqlgen::create_index<"idx_book_title", Book>("title"_c);
    return sqlite::to_sql(query);
}

}  // namespace create_index_basic
