#include <cstdio>
#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

#define nfor(i,n) for(int (i) = 0; (i) < (n); (i)++)

#define MAXN 3000
#define MAXM 3000

inline bool connected(int num_open);

int M,N;
bool closed[MAXN];
vector<int> adj[MAXN];

int main() {
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    scanf("%d %d", &N, &M);

    nfor(i,M) {
        int a,b;
        scanf("%d %d", &a, &b);

        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    nfor(i,N) {
        bool isCon = connected(N - i);
        printf(isCon ? "YES\n" : "NO\n");

        int v;
        scanf("%d", &v);
        closed[--v] = true;
    }
}

inline bool connected(int Np) {
    queue<int> q;
    nfor(v,N) {
        if(!closed[v]) {
            q.push(v);
            break;
        }
    }

    int v_count {0};
    bool visited[MAXN];
    fill_n(&visited[0], N, false);

    while(!q.empty()) {
        int v = q.front();
        q.pop();

        if(!visited[v]) {
            visited[v] = true;
            v_count++;

            for(int u: adj[v]) {
                if(!closed[u]) {
                    q.push(u);
                }
            }
        }
    }

    return v_count == Np;
}
