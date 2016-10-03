#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>

#include "acc.h"

using namespace boost::accumulators;

/**
 * @brief Demonstrates the use of Boost accumulators
 *
 * @param stats - a struct consisting of two doubles
 */
void sample_accumulate(basic_stats *stats) {
    accumulator_set<double, features<tag::mean, tag::variance>, int> acc;
    acc(8, weight = 1);
    acc(9, weight = 1);
    acc(10, weight = 4);
    acc(11, weight = 1);
    acc(12, weight = 1);
    stats->mean = mean(acc);
    stats->variance = variance(acc);
}
