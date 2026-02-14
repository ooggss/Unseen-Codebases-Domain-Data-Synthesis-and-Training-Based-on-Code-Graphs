#include <gtest/gtest.h>
#include "concat_function.hpp"

namespace concat_function {

TEST(concat_function, test_query_generation) {
    using namespace std;
    using namespace sqlgen;
    using namespace sqlgen::literals;

    vector<Person> persons = {
        {1, "John", "Doe"},
        {2, "Jane", "Smith"},
        {3, "Alice", "Johnson"}
    };

    auto conn = sqlite::connect("test_db.sqlite").value();
    drop<Person>(conn);
    create_table<Person>(conn);
    insert(conn, persons);

    vector<FullName> query_result = concat_function();
    EXPECT_EQ(query_result.size(), 3);
    EXPECT_EQ(query_result[0].full_name, "John Doe");
    EXPECT_EQ(query_result[1].full_name, "Jane Smith");
    EXPECT_EQ(query_result[2].full_name, "Alice Johnson");
}

}