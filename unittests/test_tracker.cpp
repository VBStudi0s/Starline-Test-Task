#include "gtest/gtest.h"

#include "../src/core/Tracker/Tracker.hpp"

constexpr int c_standing_time = 2*60;
constexpr int c_day_end = 23*60*60 + 59*60 + 59;

class TrackerTest : public testing::Test {
 protected:
  // TrackerTest() = default

  // ~TrackerTest() override = default;

  tracker::Tracker tr;
};

TEST_F(TrackerTest, empty)
{
    auto actual = tr.getDrivetime();
    auto expected = std::pair<int, int>({c_day_end, 0});
    EXPECT_EQ(actual, expected);
}

TEST_F(TrackerTest, Basic)
{
    tr.addTimePoint({2, 1});
    tr.addTimePoint({4, 2});
    tr.addTimePoint({6, 0});
    tr.addTimePoint({8, 1});

    auto actual = tr.getDrivetime();
    auto expected = std::pair<int, int>({c_day_end-6, 6});
    EXPECT_EQ(actual, expected);
}