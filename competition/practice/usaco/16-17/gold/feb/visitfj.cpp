#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

#define INF (1 << 30)
#define MAXN 100

int n,t_road;
int field[MAXN][MAXN];
int vis[MAXN][MAXN][3];

int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};

int main() {
    freopen("visitfj.in", "r", stdin);
    freopen("visitfj.out", "w", stdout);

    cin >> n >> t_road;
    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++) {
        cin >> field[i][j];
        for(int k: {0,1,2})
            vis[i][j][k] = INF;
    }

    queue<tuple<int,int,int,int>> q;
    q.emplace();

    while(!q.empty()) {
        int x,y,t,r;
        tie(x,y,t,r) = q.front();
        q.pop();

        // printf("(%d,%d,%d,%d)\n",x,y,t,r);
        if(0 <= x && x < n && 0 <= y && y < n) {
            if(r != 0 && r % 3 == 0) {
                t += field[x][y];
            }

            if(t < vis[x][y][r % 3]) {
                vis[x][y][r % 3] = t;

                for(int i = 0; i < 4; i++)
                    q.emplace(x + dx[i], y + dy[i], t + t_road, r + 1);
            }
        }
    }

    int *end = vis[n - 1][n - 1];
    cout << min(end[0], min(end[1], end[2]));
}
