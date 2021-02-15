#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

#define MAXN 100000

struct store { int q,p; };
ostream& operator<<(ostream& os, const store& s) {
    return os << "(" << s.q << "," << s.p << ")";
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "<";
    for(int i = 0; i < v.size() - 1; i++)
        os << v[i] << ",";
    return os << v.back() << ">";
}

int main() {
    freopen("rental.in", "r", stdin);
    freopen("rental.out", "w", stdout);

    int n,m,r;
    cin >> n >> m >> r;

    deque<int> cows(n);
    vector<int> rentals(r);
    vector<store> stores(m);

    for(int& i: cows) cin >> i;
    for(store& s: stores) cin >> s.q >> s.p;
    for(int& i: rentals) cin >> i;

    sort(cows.begin(), cows.end(), greater<int>());
    sort(stores.begin(), stores.end(),
        [](const store& a, const store& b){
            return a.p == b.p ?  a.q > b.q : a.p > b.p;
        });
    sort(rentals.begin(), rentals.end());

    int j = 0; // stores[j]
    long long total = 0;
    while(!cows.empty() && !(j == m && rentals.empty())) {
        // cout << vector<int>(cows.begin(), cows.end()) << endl;
        // cout << stores << endl << rentals << endl;
        // cout << endl;

        int k = j; // stores[k]
        int c = cows.front();
        int res = 0;

        int val = 0;
        while(c > 0 && k < m) {
            const store& s = stores[k];
            if(c == s.q) {
                val += c * s.p;
                k++;
                c = 0;
            } else if(c < s.q) {
                val += c * s.p;
                res = s.q - c;
                c = 0;
            } else { // c > s.q
                val += s.q * s.p;
                c -= s.q;
                k++;
            }
        }

        if(rentals.empty() || val >= rentals.back()) {
            total += val;
            j = k;
            stores[k].q = res;
            cows.pop_front();
        } else {
            total += rentals.back();
            rentals.pop_back();
            cows.pop_back();
        }
    }

    cout << total;
}
