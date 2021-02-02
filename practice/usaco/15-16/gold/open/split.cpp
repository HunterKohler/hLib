#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
typedef long long llong;

#define INF (1ll << 62)
#define MAXN 50000
#define first(A) (*A.begin())
#define last(A) (*--A.end())

llong min_area(llong x[], llong y[], int sx[], int n) {
    multiset<llong> y_set(y, y + n);
    llong a_min = INF, y_min = INF, y_max = -INF;
    for(int i = 0; i < n - 1; i++) {
        y_max = max(y_max, y[sx[i]]);
        y_min = min(y_min, y[sx[i]]);
        y_set.erase(y_set.find(y[sx[i]]));

        if(x[sx[i]] < x[sx[i + 1]] || y_max < first(y_set) || y_min > last(y_set)) {
            llong a1 = (x[sx[i]] - x[sx[0]]) * (y_max - y_min);
            llong a2 = (x[sx[n - 1]] - x[sx[i + 1]]) * (last(y_set) - first(y_set));
            a_min = min(a_min,a1 + a2);
        }
    }

    return a_min;
}

int main() {
    freopen("split.in", "r", stdin);
    freopen("split.out", "w", stdout);

    int n;
    int sx[MAXN],sy[MAXN];
    llong x[MAXN],y[MAXN];

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        sx[i] = sy[i] = i;
    }

    sort(sx,sx + n,[&](int i, int j){ return x[i] < x[j]; });
    sort(sy,sy + n,[&](int i, int j){ return y[i] < y[j]; });

    llong a = (x[sx[n - 1]] - x[sx[0]]) * (y[sy[n - 1]] - y[sy[0]]);
    cout << a - min(min_area(x,y,sx,n),min_area(y,x,sy,n));
}
