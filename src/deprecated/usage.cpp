#include <ostream>
#include "usage.h"

void print_usage(const std::string& exec_path, std::ostream& out) { 
    out << \
R"(Usage:
    )" << exec_path << R"( [options] pattern file
    Match regex pattern against file contents. Pass -- for file to read from 
    stdin.

Options:
    -h, --help      print this help message
    -s, --suppress  suppress all ouput
)";
}

void print_usage_short(const std::string& exec_path, std::ostream& out) { 
    out << \
"Usage: " << exec_path << R"( [options] pattern file
Run 'myregex --help' for more information.
)";
}
