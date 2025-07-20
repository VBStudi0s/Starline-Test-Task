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
    auto expected = std::pair<int, int>({c_day_end-8, 8});
    EXPECT_EQ(actual, expected);
}

TEST_F(TrackerTest, Movement)
{
    tr.addTimePoint({2, 1});
    tr.addTimePoint({4, 2});
    tr.addTimePoint({6, 2});
    tr.addTimePoint({8, 1});

    auto actual = tr.getDrivetime();
    auto expected = std::pair<int, int>({c_day_end-8, 8});
    EXPECT_EQ(actual, expected);
}

TEST_F(TrackerTest, SingleBigGap)
{
    tr.addTimePoint({2, 1});
    tr.addTimePoint({4, 2});
    tr.addTimePoint({8000, 5});
    tr.addTimePoint({8055, 1});

    auto actual = tr.getDrivetime();
    auto expected = std::pair<int, int>({c_day_end-4-55, 4+55});
    EXPECT_EQ(actual, expected);
}

TEST_F(TrackerTest, ConsecutiveZeros)
{
    tr.addTimePoint({32, 0});
    tr.addTimePoint({64, 0});
    tr.addTimePoint({96, 0});
    tr.addTimePoint({128, 0});

    auto actual = tr.getDrivetime();
    auto expected = std::pair<int, int>({c_day_end, 0});
    EXPECT_EQ(actual, expected);
}