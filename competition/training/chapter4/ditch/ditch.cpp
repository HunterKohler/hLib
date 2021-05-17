/*
ID: jhunter3
LANG: C++
TASK: ditch
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

#define FOR(i,a,b) for(int (i) = (a); (i) < (b); i++)
#define s 0
#define t M - 1
#define FORN(i,n) FOR(i,0,n)
#define MAXN 200
#define MAXM 200
#define INF (1 << 30)

using namespace std;

int bfs();

int N,M;
vector<int> adj[MAXM];
int capacity[MAXM][MAXM];
int parents[MAXM];

int main() {
    freopen("ditch.in","r",stdin);
    freopen("ditch.out","w",stdout);
    ios_base::sync_with_stdio(false);

    scanf("%d %d",&N,&M);
    FORN(i,N) {
        int u,v,c;
        scanf("%d %d %d",&u,&v,&c);
        u--; v--;
        capacity[u][v] += c;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int flow, total_flow {0};
    while(flow = bfs()) {
        total_flow += flow;
        for(int u = t; u != s; u = parents[u]) {
            capacity[parents[u]][u] -= flow;
            capacity[u][parents[u]] += flow;
        }
    }

    printf("%d\n",total_flow);
}

int bfs() {
    FORN(i,M) parents[i] = -1;
    queue<pair<int,int>> q;
    q.push({s,INF});

    while(!q.empty()) {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();

        for(int v: adj[u]) {
            if(v != s && capacity[u][v] > 0 && parents[v] == -1) {
                int new_flow = min(flow,capacity[u][v]);
                parents[v] = u;
                if(v == t) {
                    return new_flow;
                }
                q.push({v,new_flow});
            }
        }
    }
    return 0;
}
