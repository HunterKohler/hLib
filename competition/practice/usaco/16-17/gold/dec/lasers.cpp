#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

#define MAXN 100000
#define INF (1 << 30)

int n,b = 0, l = 1;
int x[MAXN],y[MAXN],vis[MAXN];
int sx[MAXN],sy[MAXN];

int main() {
    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);

    cin >> n >> x[b] >> y[b] >> x[l] >> y[l];
    for(int i = 2; i < n + 2; i++) {
        cin >> x[i] >> y[i];
    }
    n += 2;

    queue<tuple<int,int,int>> q;
    q.emplace(b,b,0);

    vector<int> adj[MAXN];

    for(int i = 0; i < n; i++) {
        vis[i] = INF;
        sx[i] = i;
        sy[i] = i;
    }

    sort(sx,sx + n,[](int i, int j) { return x[i] < x[j]; });
    sort(sy,sy + n,[](int i, int j) { return y[i] < y[j]; });

    for(int i = 0, j = 1; i < n; i = j++) {
        while(j < n && x[sx[i]] == x[sx[j]]) {
            adj[sx[i]].push_back(sx[j]);
            adj[sx[j]].push_back(sx[i]);
            j++;
        }
    }

    for(int i = 0, j = 1; i < n; i = j++) {
        while(j < n && y[sy[i]] == y[sy[j]] && x[sy[i]] != x[sy[j]]) {
            adj[sy[i]].push_back(sy[j]);
            adj[sy[j]].push_back(sy[i]);
            j++;
        }
    }

    while(!q.empty()) {
        int u,f,m;
        tie(u,f,m) = q.front();
        q.pop();

        if(m < vis[u]) {
            vis[u] = m;

            int dfx = f == -1 ? 0 : abs(x[f] - x[u]);
            int dfy = f == -1 ? 0 : abs(y[f] - y[u]);

            for(int v: adj[u]){
                int dx = abs(x[v] - x[u]);
                int dy = abs(y[v] - y[u]);

                if(f != -1 && ((dx && dfy) || (dy && dfx)))
                    q.emplace(v,u,m + 1);
                else
                    q.emplace(v,u,m);
            }
        }
    }

    cout << (vis[l] == INF ? -1 : vis[l]);
}
