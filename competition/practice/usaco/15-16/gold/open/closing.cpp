#include <iostream>
#include <vector>
#include <stack>

using namespace std;

#define MAXN 200000

int n,m,c;
int parent[MAXN];
bool open[MAXN];
stack<int> order;
stack<bool> res;
vector<int> adj[MAXN];

int root(int u) {
    return parent[u] == u ? u : parent[u] = root(parent[u]);
}

bool join(int u,int v) {
    if((u = root(u)) == (v = root(v)) || !open[u] || !open[v])
        return false;
    if(rand() % 2) parent[v] = u;
    else parent[u] = v;
    return true;
}

int main() {
    !freopen("closing.in", "r", stdin);
    !freopen("closing.out", "w", stdout);

    cin >> n >> m;

    for(int i = 0; i < m; i++) {
        int u,v;
        cin >> u >> v;
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }

    for(int i = 0; i < n; i++) {
        int u;
        cin >> u;
        order.push(u-1);
        parent[i] = i;
    }

    c = 0;
    while(!order.empty()) {
        int u = order.top();
        order.pop();

        open[u] = true;
        c++;
        for(int v: adj[u])
            c -= join(u,v);
        res.push(c == 1);
    }

    while(!res.empty()) {
        cout << (res.top() ? "YES" : "NO") << endl;
        res.pop();
    }
}
