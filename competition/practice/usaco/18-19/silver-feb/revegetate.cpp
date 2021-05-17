#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

#define MAXN 100000

int n,m;
vector<pair<int,char>> adj[MAXN];
bool color[MAXN], visited[MAXN];

bool dfs(int v) {
    visited[v] = true;
    int u; char t;
    for(pair<int,char>& p: adj[v]) {
        tie(u,t) = p;

        if(visited[u]) {
            if((color[u] == color[v]) != (t == 'S'))
                return false;
        } else {
            color[u] = t == 'S' ? color[v] : !color[v];
            if(!dfs(u))
                return false;
        }
    }

    return true;
}

int main() {
    freopen("revegetate.in", "r", stdin);
    freopen("revegetate.out", "w", stdout);

    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        char t;
        int v,u;
        cin >> t >> v >> u;
        v--; u--;
        adj[v].emplace_back(u,t);
        adj[u].emplace_back(v,t);
    }

    int comps = 0;
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            if(dfs(i))
                comps++;
            else {
                cout << 0;
                return 0;
            }
        }
    }

    cout << 1;
    for(int i = 0; i < comps; i++)
        cout << 0;
}
