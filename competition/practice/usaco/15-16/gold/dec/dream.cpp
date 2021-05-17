#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

#define MAXN 1000
#define INF (1 << 30)

enum color { red, pink, orange, blue, purple };
typedef tuple<int,int,int,int,bool> state;
// state : (x,y,dir,dist,smell)

void println(state s) {
    int x,y,dir,dist;
    bool smell;
    tie(x,y,dir,dist,smell) = s;
    printf("(%d,%d,%d,%d,%d)\n",x,y,dir,dist,smell);
}

int n,m;
int g[MAXN][MAXN];
int mem[MAXN][MAXN][4][2]; // s[x][y][dir][smell]
int dx[] {0,1,0,-1}; // dir: n,s,e,w - 0,1,2,3;
int dy[] {1,0,-1,0};

inline bool in_grid(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m;
}

int main() {
    freopen("dream.in", "r", stdin);
    freopen("dream.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scanf("%d %d",&n,&m);
    for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++) {
        scanf("%d",&g[i][j]);
        for(int a: {0,1,2,3})
        for(int b: {0,1})
            mem[i][j][a][b] = INF;
    }

    queue<state> q;
    q.emplace();
    int x,y,dir,dist;
    bool smell;
    while(!q.empty()) {
        tie(x,y,dir,dist,smell) = q.front();
        q.pop();

        // println(s);

        if(
            in_grid(x,y) &&
            g[x][y] != red &&
            (g[x][y] != blue || smell) &&
            dist < mem[x][y][dir][smell]
        ) {
            if(g[x][y] == purple) {
                smell = false;
                mem[x][y][dir][smell] = dist;

                int xn = x + dx[dir];
                int yn = y + dy[dir];

                q.emplace(xn,yn,dir,dist + 1,smell);
            } else {
                smell |= g[x][y] == orange;
                for(int i:{0,1,2,3}) {
                    mem[x][y][i][smell] = dist;
                    int xn = x + dx[i];
                    int yn = y + dy[i];
                    q.emplace(xn,yn,i,dist + 1,smell);
                }
            }
        }
    }

    int min_dist = INF;
    for(int a:{0,1,2,3})
    for(int b:{0,1})
        min_dist = min(min_dist, mem[n - 1][m - 1][a][b]);

    cout << (min_dist == INF ? -1 : min_dist);
}
