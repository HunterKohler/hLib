#include <iostream>
#include <algorithm>
#include <exception>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <fstream>
#include <bitset>

class LSFR {
  private:
    size_t n; // length
    bool* seed; // polynomial
    bool* bregister; // register
    std::vector<bool> gen; // outputs

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

    LSFR(const std::vector<bool>& _seed): LSFR(_seed.size())
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

    std::vector<bool> operator()(int bits) {
        std::vector<bool> result;
        for(int i = 0; i < bits; i++)
            result.push_back(next());
        return result;
    }

    void check_last() {
        if(!seed[n-1] || !bregister[n-1]) {
            throw std::invalid_argument("Last bit must be set in LSFR.");
        }
    }

    friend std::ostream& operator<<(std::ostream&, const LSFR&);
};
