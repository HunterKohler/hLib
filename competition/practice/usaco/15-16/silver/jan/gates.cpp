#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

#define for_n(i,n) for(int (i) = 0; (i) < (n); (i)++)
#define MAX_N 1000
#define MAX_W (2 * MAX_N + 1)

bool in_grid(int x, int y) {
    return 0 <= x && x < MAX_W && 0 <= y && y < MAX_W;
}

ostream& operator<<(ostream& os, const pair<int,int> p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

int n;
bool adj[MAX_W][MAX_W][4];
bool vis[MAX_W][MAX_W];
int main() {
    freopen("gates.in","r",stdin);
    freopen("gates.out","w",stdout);



    for_n(i,MAX_W)
    for_n(j,MAX_W) {
        vis[i][j] = false;
        adj[i][j][0] = in_grid(i, j + 1);
        adj[i][j][1] = in_grid(i + 1, j);
        adj[i][j][2] = in_grid(i, j - 1);
        adj[i][j][3] = in_grid(i - 1, j);
    }

    { // INPUT
        cin >> n;
        int x = MAX_N, y = MAX_N;
        for(char c; cin >> c;) {
            if(c == 'N') y++;
            if(c == 'E') x++;

            if(c == 'N' || c == 'S') {
                adj[x - 1][y][1] = false;
                adj[x + 1][y][3] = false;
            }

            if(c == 'E' || c == 'W') {
                adj[x][y + 1][2] = false;
                adj[x][y - 1][0] = false;
            }

            if(c == 'S') y--;
            if(c == 'W') x--;
        }
    } // END INPUT

    int components = 0;
    for_n(i,MAX_W)
    for_n(j,MAX_W) {
        if(!vis[i][j]) {
            components++;

            queue<pair<int,int>> q;
            q.emplace(i,j);

            while(!q.empty()) {
                int x = q.front().first,
                    y = q.front().second;
                q.pop();

                if(!vis[x][y]) {
                    vis[x][y] = true;

                    if(adj[x][y][0]) q.emplace(x, y + 1);
                    if(adj[x][y][1]) q.emplace(x + 1, y);
                    if(adj[x][y][2]) q.emplace(x, y - 1);
                    if(adj[x][y][3]) q.emplace(x - 1, y);
                }
            }
        }
    }

    cout << components - 1;
}
