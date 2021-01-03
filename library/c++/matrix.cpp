#include <ostream>
#include <vector>

template<class T>
using matrix = std::vector<std::vector<T>>;

template<class T>
std::ostream& operator<<(std::ostream& os, const matrix<T>& m) {
    int l = 0;
    for(const std::vector<T>& v: m) {
        os << (l == 0 ? "{{" : " {");
        int i_v = 0;
        for(const T& i: v)
            os << i << (++i_v == v.size() ? "" : ", ");
        os << (++l == m.size() ? "}" : "}\n");
    }
    os << "}\n";
    return os;
}
