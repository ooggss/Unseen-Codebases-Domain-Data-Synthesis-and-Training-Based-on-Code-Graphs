#include <gtest/gtest.h>
#include "coalesce_function.hpp"
#include <algorithm>
#include <cctype>

namespace coalesce_function {
TEST(coalesce_function, test_query_generation) {
    using namespace std;
    using namespace sqlgen;
    using namespace sqlgen::literals;
    vector<Profile> profiles = vector<Profile>{
        {1, "Bob"},
        {2, nullopt},
        {3, "Alice"}
    };
    auto conn = sqlite::connect("test_db.sqlite").value();
    drop<Profile>(conn);
    create_table<Profile>(conn);
    insert(conn, profiles);

    vector<NicknameResult> query_result = coalesce_function();
    EXPECT_EQ(query_result.size(), 3);
    EXPECT_EQ(query_result[0].display_name, "Bob");
    EXPECT_EQ(query_result[1].display_name, "Anonymous");
}
}