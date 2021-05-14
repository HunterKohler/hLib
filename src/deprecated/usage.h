#ifndef MYREGEX_USAGE_H_
#define MYREGEX_USAGE_H_

#include <iostream>
#include <string>

void print_usage(const std::string& exec_path, std::ostream& out = std::cout);
void print_usage_short(const std::string& exec_path, std::ostream& out = std::cout);

#endif