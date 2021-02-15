#include <iostream>
#include <algorithm>
#include <tuple>
#include

using namespace std;

#define MAXN 100000
#define INF (1 << 30)

int n, d;
int b[2*MAXN], e[2*MAXN],
    bs[2*MAXN], es[2*MAXN],
    vis[2*MAXN], zdist[2*MAXN];

int main() {
    !freopen("piepie.in", "r", stdin);
    !freopen("piepie.out", "w", stdout);

    cin >> n >> d;
    for(int i = 0; i < 2*n; i++) {
        cin >> b[i] >> e[i];
        bs[i] = es[i];
    }

    sort(bs, bs + (2*n),
        [](int i, int j) {
            return b[i] < b[j];
        });
    sort(es, es + (2*n),
        [](int i, int j) {
            return e[i] < e[j];
        });

    queue<tuple<int,int,bool>> q; // <*s index,dist>
    for(int i = 0; i < n; i++) {
        if(b[bs[i]] == 0) {
            q.emplace(b[bs[i]],0,true);
        if(e[es[i + n]] == 0) {
            q.emplace(e[es[i + n]],0,false);
        dist[i] = INF;
    }

    while(!q.empty()) {
        int index,dist;
        tie(index, dist) = q.front();
        q.pop();

        if(index < n) {

        } else {

        }

    }
}
