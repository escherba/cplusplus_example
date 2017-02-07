#include <iostream>
#include <gflags/gflags.h>
#include <boost/filesystem.hpp>
#include "acc.h"


DEFINE_bool(verbose, false, "Display program name before message");
DEFINE_string(message, "Hello world!", "Message to print");
DEFINE_string(infile, "-", "file");


int main(int argc, char *argv[])
{
    gflags::SetUsageMessage("some usage message");
    gflags::SetVersionString("1.0.0");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    if (FLAGS_verbose) std::cout << gflags::ProgramInvocationShortName() << ": ";
    std::cout << FLAGS_message << std::endl;
    gflags::ShutDownCommandLineFlags();

    std::string file_ext = boost::filesystem::extension(FLAGS_infile);

    std::cout << "extension was: " << file_ext << std::endl;
    basic_stats stats;
    sample_accumulate(&stats);

    std::cout << stats.mean << '\n';
    std::cout << stats.variance << '\n';

    return 0;
}
