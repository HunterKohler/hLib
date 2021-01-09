#include <vector>

// needs testing
template <class T, size_t D>
struct nd_vector : public std::vector<nd_vector<T, D - 1> > {
    const size_t dimension = D;
    static_assert(D >= 1, "Dimension must be 1 or greater.");

    template <class ... >
    nd_vector(int n = 0, U ... args)
        : std::vector<nd_vector<T, D - 1>>(n, nd_vector<T, D - 1>(args...)){ }
};

template <class T>
struct nd_vector<T, 1> : public std::vector<T> {
    const size_t dimension = 1;
    nd_vector(int n = 0, const T& v = T()) : std::vector<T>(n, v){ }
};

int main(){ }
