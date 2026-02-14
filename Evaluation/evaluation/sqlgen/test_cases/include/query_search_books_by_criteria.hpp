#pragma once

#include <optional>
#include <ranges>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace query_search_books_by_criteria {

struct Book {
  sqlgen::PrimaryKey<int> book_id;
  std::string title;
  std::string author;
  int year;
  std::string genre;
  double price;
};

struct BookFilters {
  std::optional<std::string> title_keyword;
  std::optional<int> min_year;
  std::optional<std::string> genre;
  std::optional<double> max_price;
};

struct BookSearchResults {
  static constexpr const char* tablename = "BookSearchResults";
  static constexpr bool is_view = true;
  sqlgen::PrimaryKey<int> book_id;
  std::string title;
  std::string author;
  int year;
  std::string genre;
  double price;
};

/**
 * Function: Search for books based on multiple optional criteria.
 * @param filters Optional filters for title, year, genre, and price
 * @return List of books matching the criteria
 */
std::vector<Book> query_search_books_by_criteria(const BookFilters& filters) {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn_result = sqlite::connect("test_db.sqlite");
  if (!conn_result) return {};
  auto conn = conn_result.value();

  // Create table if not exists (helper for standalone run)
  create_table<Book>(conn);
  
  std::string sql = "SELECT * FROM Book WHERE 1=1";
  
  if (filters.title_keyword) {
    sql += " AND title LIKE '%" + filters.title_keyword.value() + "%'";
  }
  if (filters.min_year) {
    sql += " AND year >= " + std::to_string(filters.min_year.value());
  }
  if (filters.genre) {
    sql += " AND genre = '" + filters.genre.value() + "'";
  }
  if (filters.max_price) {
    sql += " AND price <= " + std::to_string(filters.max_price.value());
  }
  
  exec(conn, "DROP VIEW IF EXISTS BookSearchResults");
  std::string view_sql = "CREATE VIEW BookSearchResults AS " + sql;
  exec(conn, view_sql);
  
  auto results = sqlgen::read<std::vector<BookSearchResults>>(conn).value();
  
  std::vector<Book> out;
  out.reserve(results.size());
  for (const auto& r : results) {
    out.push_back({r.book_id, r.title, r.author, r.year, r.genre, r.price});
  }
  return out;
}

}  // namespace query_search_books_by_criteria
