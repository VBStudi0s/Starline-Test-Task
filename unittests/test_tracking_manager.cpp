#include "gtest/gtest.h"

#include "../src/core/TrackingManager/TrackingManager.hpp"

constexpr int c_standing_time = 2*60;
constexpr int c_day_end = 23*60*60 + 59*60 + 59;

class TrackingManagerTest : public testing::Test {
 protected:
  // TrackerTest() = default

  // ~TrackerTest() override = default;

  tracker::TrackingManager tm;
};

TEST_F(TrackingManagerTest, Basic)
{
    tm.addTimePoint("123", {2, 1});
    tm.addTimePoint("456", {4, 2});
    tm.addTimePoint("123", {6, 0});
    tm.addTimePoint("456", {8, 1});

    auto actual = tm.getDrivetimeByID("123");
    auto expected = std::pair<int, int>({c_day_end-6, 6});
    EXPECT_EQ(actual, expected);

    auto actual2 = tm.getDrivetimeByID("456");
    auto expected2 = std::pair<int, int>({c_day_end-8, 8});
    EXPECT_EQ(actual2, expected2);
}