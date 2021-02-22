#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

#define MAXN 100000

int N,Q;

int tree_size[MAXN];
int parent[MAXN];

void init() {
    for(int i = 0; i < MAXN; i++) {
        parent[i] = i;
    }
}

int root(int v) {
    return parent[v] = (parent[v] == v ? v : root(parent[v]));
}

void join(int v,int u) {
    v = root(v);
    u = root(u);

    if(v != u) {
        tree_size[v] += tree_size[u] + 1;
        parent[u] = v;
        tree_size[u] = 0;
    }
}

int size(int v) {
    return tree_size[root(v)];
}

int main() {
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);

    init();

    cin >> N >> Q;

    priority_queue<tuple<int,int,int>> eq;
    for(int i = 0; i < N - 1; i++) {
        int v,u,w;
        cin >> v >> u >> w;
        eq.emplace(w,v-1,u-1);
    }

    priority_queue<tuple<int,int,int>> qq;
    for(int i = 0; i < Q; i++) {
        int k,v;
        cin >> k >> v;
        qq.emplace(k,v-1,i);
    }

    vector<int> ans(Q);
    while(!qq.empty()) {
        int k,v,i;
        tie(k,v,i) = move(qq.top());

        while(!eq.empty() && get<0>(eq.top()) >= k) {
            join(get<1>(eq.top()), get<2>(eq.top()));
            eq.pop();
        }

        ans[i] = size(v);
        qq.pop();
    }

    for(int a: ans) {
        cout << a << endl;
    }
}
