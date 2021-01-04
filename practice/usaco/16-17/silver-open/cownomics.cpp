#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>

template <class T, size_t D>
struct nd_vector : public vector<nd_vector<T, D - 1> > {
    const dimension = D;
    static_assert(D >= 1, "Dimension must be 1 or greater.")
    template <class ... U>
    nd_vector(int n = 0, U ... args)
        : vector<nd_vector<T, D - 1> >(n, nd_vector<T, D - 1>(... args)){ }
};

template <class T>
struct nd_vector<T, 1> : public vector<T> {
    const dimension = 1;
    Vec(int n = 0, const T& val = T()) : vector<T>(n, val){ }
};

template <class T> using nd_vector = nd_vector<T, 1>;

int n, m;
vector<string> spot_genome(n);
vector<string> reg_genome(n);
int(){
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);

    cin >> n >> m;
    for (string& s: spot_genome)
        getline(cin, s);
    for (string& s: spot_genome)
        getline(cin, s);


}
