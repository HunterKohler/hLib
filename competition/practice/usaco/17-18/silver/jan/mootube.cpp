#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define INF (1 << 30)

int main() {
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);

    int N,Q;
    cin >> N >> Q;

    vector<vector<pair<int,int>>> adj(N);
    for(int i = 0; i < N - 1; i++) {
        int p,q,r;
        cin >> p >> q >> r;

        p--;q--;
        adj[p].emplace_back(q,r);
        adj[q].emplace_back(p,r);
    }

    vector<vector<int>> dist(N, vector<int>(N));
    for(int i = 0; i < N; i++) {
        vector<bool> vis(N);
        queue<pair<int,int>> q;
        q.emplace(i,INF);

        while(!q.empty()) {
            int p = q.front().first;
            int r = q.front().second;
            q.pop();

            if(!vis[p]) {
                vis[p] = true;
                dist[i][p] = r;
                for(pair<int,int>& e: adj[p])
                    q.emplace(e.first, min(r,e.second));
            }
        }
    }

    for(int i = 0; i < Q; i++) {
        int k,v;
        cin >> k >> v;
        v--;
        int total = -1;
        for(int j: dist[v])
            total += (j >= k);

        cout << total << endl;
    }
}
