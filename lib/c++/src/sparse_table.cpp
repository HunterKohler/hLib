#include <cmath>
#include <algorithm>
#include <iostream>

using std::min;

inline int ilog2(int x) {
    return (int) ( std::log2(x) + 1);
}

// Range query with answer functor F returning answer (ints only)
template <class F>
class sparse_table {
  private:
    F f;
    int **spt; // stores answer on range a[i,i+1,...,i+2^j-1]
    int n;

  public:
    sparse_table(int a[], int _n): f{}, n{_n} {
        spt = new int*[n];
        for(int i = 0; i < n; i++) {
            spt[i] = new int[ilog2(n)];
            spt[i][0] = f(i,i);
        }

        for(int j = 1; (1 << j) <= n; j++)
        for(int i = 0; i + (1 << j) <= n; i++)
            spt[i][j] = f(spt[i][j-1], spt[i+(1<<(j-1))][j-1]);
    }

    ~sparse_table() {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < ilog2(n); j++)
                delete spt[i][j];
            delete[] spt[i];
        }

        delete[] spt;
    }

    int query(int i, int j) {
        int k = ilog2(i-j+1);
        return min(spt[i][j],spt[i]);
    }
};

template <class T> using cmp = bool(*)(const T&,const T&);

template <class T>
struct funct_cmp {
  protected:
    cmp<T> _f;

  public:
    funct_cmp(cmp<T> f): _f{f} {};
    const T& operator()(const T& a, const T& b) {
        return  _f(a,b) ? a : b;
    }
};

template<class T>
bool less(const T& a, const T& b) {
    return a < b;
}

template<class T>
bool greater(const T& a, const T& b) {
    return a > b;
}

using std::cout;
using std::cin;
using std::endl;
using std::boolalpha;

int main() {

}
