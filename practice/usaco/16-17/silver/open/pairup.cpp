#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define MAXN 100000

int main() {
    freopen("pairup.in","r",stdin);
    freopen("pairup.out","w",stdout);

    int n;
    cin >> n;

    vector<pair<int,int>> xy;
    for(int x,y; cin >> x >> y;)
        xy.emplace_back(x,y);

    sort(xy.begin(), xy.end(),
        [](const pair<int,int>& p, const pair<int,int>& q) {
            return p.second < q.second;
        });

    auto b = xy.begin(),
        e = xy.end();

    int m = 0;
    while(b <= e) {
        m = max(m, b->second + e->second);
        if(b->first < e->first) {
            e->first -= (b++)->first;
        } else if(b->first > e->first) {
            b->first -= (e--)->first;
        } else {
            b++; e--;
        }
    }

    cout << m;
}
