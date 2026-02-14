#include <gtest/gtest.h>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include "create_index_basic.hpp"

namespace create_index_basic {

TEST(create_index_basic, test_query_generation) {
    using namespace std;
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto conn = sqlite::connect("test_db.sqlite").value();
    drop<Book>(conn);
    create_table<Book>(conn);
    string sql = create_index_basic();
    
    EXPECT_TRUE(sql.find("CREATE INDEX") != std::string::npos);
    EXPECT_TRUE(sql.find("idx_book_title") != std::string::npos);
    EXPECT_TRUE(sql.find("ON") != std::string::npos);
    EXPECT_TRUE(sql.find("Book") != std::string::npos);
    EXPECT_TRUE(sql.find("title") != std::string::npos);
}

}