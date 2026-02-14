#include <gtest/gtest.h>
#include "update_with_arithmetic.hpp"

namespace update_with_arithmetic {

TEST(update_with_arithmetic, test_query_generation) {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto conn = sqlite::connect("test_db.sqlite").value();
    std::vector<Player> players = {
        {1, 0},
        {2, 10},
    };
    drop<Player>(conn);
    create_table<Player>(conn);
    insert(conn, players);
    auto updated_players = update_with_arithmetic();
    EXPECT_EQ(updated_players.size(), 2);
    EXPECT_EQ(updated_players[0].score, 10);
    EXPECT_EQ(updated_players[1].score, 20);
}

}