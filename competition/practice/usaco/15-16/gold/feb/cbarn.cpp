#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cassert>

using namespace std;

inline int sq(int x) { return x * x; }

int main() {
    !freopen("cbarn.in", "r", stdin);
    !freopen("cbarn.out", "w", stdout);

    int n;
    cin >> n;

    vector<priority_queue<
        tuple<int,int>,
        vector<tuple<int,int>>,
        greater<tuple<int,int>>
    >> c;
    for(int m; cin >> m;) {
        c.emplace_back();
        for(int i = 0; i < m; i++)
            c.back().emplace(0,c.size() - 1);
    }

    bool change = true;
    int carry_i = -1, carry_d;
    while(change) {
        change = false;
        for(auto& q: c) {
            if(carry_i == -1) {
                if(q.size() > 1) {
                    tie(carry_d, carry_i) = q.top();
                    q.pop();
                }
            } else {
                q.emplace(carry_d, carry_i);
                carry_d = 0;
                carry_i = -1;
                if(q.size() > 1) {
                    tie(carry_d, carry_i) = q.top();
                    q.pop();
                }
            }

            if(carry_i != -1) {
                change = true;
                carry_d = (carry_d + 1) % n;
            }
        }
    }

    long long s = 0;
    for(auto& q: c)
        s += sq(get<0>(q.top()));
    cout << s;
}
