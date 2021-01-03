#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

#define FOR(i,n) for(int (i) = 0; (i) < (n); (i)++)
#define INF (1 << 30)

#define MAXX 100
#define MAXY 100
#define MAXK 100
#define MAXM 200

int X,Y,K,M;
int dist[MAXX + 1][MAXY + 1];

inline int min(int a, int b) {
    return (a < b) ? a : b;
}

struct state {
    int x,y,k;
    inline bool valid() {
        return x <= X && y <= Y && k <= K;
    }
};

int main() {
    FOR(i, MAXX + 1) FOR(j, MAXY + 1) dist[i][j] = INF;

    freopen("pails.in","r",stdin);
    freopen("pails.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scanf("%d %d %d %d",&X,&Y,&K,&M);

    int Mp {INF};
    queue<state> q;
    q.push({0,0,0});
    while(!q.empty()) {
        int x {q.front().x},
            y {q.front().y},
            k {q.front().k};
        q.pop();

        if(k < dist[x][y]) {
            dist[x][y] = k++;
            Mp = min(Mp, abs(x + y - M));

            for(state i: (state[6]) {
                { X, y, k },
                { x, Y, k },
                { 0, y, k },
                { x, 0, k },
                { min(x + y, X), y - min(y, X - x), k },
                { x - min(x, Y - y), min(x + y, Y), k}
            }) {
                if(i.valid()) {
                    q.push(i);
                }
            }
        }
    }

    printf("%d\n", Mp);
}
