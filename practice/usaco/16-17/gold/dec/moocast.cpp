#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define sq(a) ((a)*(a))
#define mag(a) (sq(x[(a).u] - x[(a).v]) + sq(y[(a).u] - y[(a).v]))
#define MAXN 1000

struct edge { int u,v; };

int n;
int x[MAXN],y[MAXN];
vector<edge> e;
int p[MAXN];

int root(int u) {
    return u == p[u] ? u : p[u] = root(p[u]);
}

bool join(int u, int v) {
    if((u = root(u)) == (v = root(v)))
        return false;
    // cout << "what";
    p[u] = v;
    return true;
}

int main() {
    !freopen("moocast.in", "r", stdin);
    !freopen("moocast.out", "w", stdout);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        for(int j = 0; j < i; j++)
            e.push_back({j,i});
    }

    sort(e.begin(), e.end(),
        [](const edge& a, const edge& b) {
            return mag(a) < mag(b);
        });

    for(int i = 0; i < n; i++)
        p[i] = i;

    int m = 0;
    for(edge a: e)
        m = max(m,join(a.u,a.v) * mag(a));

    cout << m;
}
