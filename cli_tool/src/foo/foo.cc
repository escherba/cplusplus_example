#include <iostream>
#include <gflags/gflags.h>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>

#include "foo.h"


DEFINE_bool(verbose, false, "Display program name before message");
DEFINE_string(message, "Hello world!", "Message to print");

using namespace boost::accumulators;


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

int main(int argc, char *argv[])
{
    gflags::SetUsageMessage("some usage message");
    gflags::SetVersionString("1.0.0");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    if (FLAGS_verbose) std::cout << gflags::ProgramInvocationShortName() << ": ";
    std::cout << FLAGS_message << std::endl;
    gflags::ShutDownCommandLineFlags();

    basic_stats stats;
    sample_accumulate(&stats);

    std::cout << stats.mean << '\n';
    std::cout << stats.variance << '\n';

    return 0;
}
