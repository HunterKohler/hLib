#include <iostream>
#include <algorithm>
#include <exception>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <fstream>

using std::cout;
using std::endl;
using std::fill_n;
using std::size_t;
using std::vector;
using std::bitset;
using std::ostream;

class LSFR {
  private:
    size_t n; // length
    bool* seed; // polynomial
    bool* bregister; // register
    vector<bool> gen; // outputs

    LSFR(size_t _n): n{_n}, seed{new bool[_n]}, bregister{new bool[_n]} {}

  public:
    LSFR(size_t _n, bool *_seed): LSFR(_n)
    {
        std::copy(_seed,_seed + n,seed);
        std::copy(_seed,_seed + n,bregister);
        check_last();
    }

    LSFR(size_t _n, bool *_seed, bool *_bregister): LSFR(_n)
    {
        std::copy(_seed,_seed + n,seed);
        std::copy(_seed,_seed + n,bregister);
        check_last();
    }

    LSFR(const vector<bool>& _seed): LSFR(_seed.size())
    {
        std::copy(_seed.begin(),_seed.end(),seed);
        std::copy(_seed.begin(),_seed.end(),bregister);
        check_last();
    }

    LSFR(const LSFR& lsfr): LSFR(lsfr.n,lsfr.seed,lsfr.bregister) {}
    LSFR(LSFR&& lsfr)
    {
        n = lsfr.n;
        seed = lsfr.seed;
        bregister = lsfr.bregister;
        gen = std::move(lsfr.gen);

        lsfr.n = 0;
        lsfr.seed = nullptr;
        lsfr.bregister = nullptr;
    }

    ~LSFR() {
        delete[] seed;
        delete[] bregister;
    }

    bool next() {
        bool curr = bregister[n-1];
        bool bit = 0;

        for(int i = n - 1; i > 0; i--) {
            bit ^= seed[i] * bregister[i];
            bregister[i] = bregister[i-1];
        }

        bregister[0] = bit;
        gen.push_back(curr);
        return curr;
    }

    vector<bool> operator()(int bits) {
        vector<bool> result;
        for(int i = 0; i < bits; i++)
            result.push_back(next());
        return result;
    }

    void check_last() {
        if(!seed[n-1] || !bregister[n-1]) {
            throw std::invalid_argument("Last bit must be set in LSFR.");
        }
    }

    friend ostream& operator<<(ostream&, const LSFR&);
};

ostream& operator<<(ostream& os, const LSFR& lsfr) {
    os << "bregister: ";
    for(int i = 0; i < lsfr.n; i++) os << lsfr.bregister[i];
    os << endl << "seed: ";
    for(int i = 0; i < lsfr.n; i++) os << lsfr.seed[i];
    return os;
}

bool* to_bool_array(int x) {
    bool* arr = new bool[30];
    for(int i = 0; i < 30; i++)
        arr[i] = x & (1 << i);
    return arr;
}

bool* to_bool_array(const char* x, int l) {
    bool* arr = new bool[l * 8];
    for(int i = 0; i < l; i++)
    for(int j = 0; j < 8; j++)
        arr[i*8+j] = x[i] & (1 << j);
    return arr;
}

int main() {

    bool* key = to_bool_array("thisislg10",10);
    key[79] = 1;
    LSFR lsfr(80,key);

    std::ifstream fin("doc.txt");
    std::ofstream fout("out.txt");
    int x = 0;
    for(char c; fin >> c;) {
        x++;
        for(int i = 0; i < 8; i++)
            c ^= lsfr.next() << i;
        fout << c;
    }

    cout << x << endl;
}
