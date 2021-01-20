#include <iostream>
#include <tuple>
#include <queue>

using namespace std;

#define W 1001

int n,k;
int prefix[W][W];
bool vis[W][W];

int dfs(int x, int y) {
    if(x < 0 || y < 0)
        return 0;

    if(!vis[x][y]) {
        vis[x][y] = true;

        prefix[x][y] += dfs(x-1,y) + dfs(x,y-1) - dfs(x-1,y-1);
    }

    return prefix[x][y];
}

int main() {
    freopen("paintbarn.in", "r", stdin);
    freopen("paintbarn.out", "w", stdout);

    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        int x0,y0,xf,yf;
        cin >> x0 >> y0 >> xf >> yf;
        prefix[x0][y0]++;
        prefix[x0][yf]--;
        prefix[xf][y0]--;
        prefix[xf][yf]++;
    }

    int t = 0;
    for(int x = 0; x < W; x++)
    for(int y = 0; y < W; y++)
        t += dfs(x,y) == k;
    cout << t;
}
