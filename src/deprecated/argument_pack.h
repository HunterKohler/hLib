#ifndef MYREGEX_ARGUMENT_PACK_H_
#define MYREGEX_ARGUMENT_PACK_H_

#include <vector>
#include <string>
#include <ostream>

#include "printer.h"

class ArgumentPack {
  public:
    using size_type = std::size_t;
    using container = std::vector<std::string>;
    using iterator = container::const_iterator;
    using const_iterator = container::const_iterator;

    const std::string exec_name;

    inline ArgumentPack(int argc, const char* argv[]): 
        exec_name(argv[0]),
        args(argv + 1, argv + argc)
    {}

    inline const std::string& operator[](size_type i) const { return args[i]; }

    inline size_type size() const { return args.size(); }

    inline const_iterator begin() const { return args.begin(); }
    inline const_iterator end() const { return args.end(); }

    // friend inline std::ostream& operator<<(std::ostream& os, const ArgumentPack& args);

  private:
    const std::vector<std::string> args;
};

// inline std::ostream& operator<<(std::ostream& os, const ArgumentPack& ap) {
//     return os << ap.args;
// }

#endif