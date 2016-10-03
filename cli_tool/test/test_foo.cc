#include "gtest/gtest.h"
#include "acc.h"

TEST(foo_test, mean_variance)
{
    basic_stats stats;
    sample_accumulate(&stats);

    EXPECT_EQ(stats.mean, 10.0);
    EXPECT_EQ(stats.variance, 1.25);
}
