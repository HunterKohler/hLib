#include <iostream>
#include <algorithm>

using namespace std;

#define INF (1ll << 60)
#define MAXN 50000

int n;
long long x[MAXN], y[MAXN], sx[MAXN];

int main() {
    !freopen("split.in", "r", stdin);
    !freopen("split.out", "w", stdout);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        sx[i] = i;
    }

    sort(sx, sx + n, [](int i, int j){return x[i] < x[j];});

    set<int> s;
    ll min_y = INF, max_y = 0;
    for()
}
