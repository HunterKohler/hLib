#ifndef UTILS_H_
#define UTILS_H_

#include <string>

int bitcount(int);

int hamming_distance(const std::string&, const std::string&);
int hamming_distance(const std::string_view&,const std::string_view&);

std::string get_file_contents(const char*);

int random_int();
int random_int(int);
int random_int(int,int);

#endif
