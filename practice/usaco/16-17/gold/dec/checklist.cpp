#include <iostream>
#include <cassert>
#include <tuple>
#include <queue>

using namespace std;

#define MAXN 1000
#define INF (1 << 30)
#define sq(x) ((x)*(x))
#define dist(x,y,u,v) (sq((x)-(u))+sq((y)-(v)))

int h,g;
int hx[MAXN],hy[MAXN],gx[MAXN],gy[MAXN];
int vis[MAXN][MAXN][2]; // [h,g, (true = on h) (false = on g)] = min_score

int main() {
    !freopen("checklist.in", "r", stdin);
    !freopen("checklist.out", "w", stdout);

    cin >> h >> g;
    for(int i = 0; i < h; i++)
        cin >> hx[i] >> hy[i];
    for(int i = 0; i < g; i++)
        cin >> gx[i] >> gy[i];

    for(int i = 0; i < MAXN; i++)
    for(int j = 0; j < MAXN; j++)
    for(bool s: {true,false})
        vis[i][j][s] = INF;

    for(int i = 0; i < MAXN; i++)
    for(int j = 0; j < MAXN; j++)
    for(bool s: {true,false})
        vis[i][j][s] = INF;

    queue<tuple<int,int,int,int>> q;
    q.emplace(0,-1,true,0);

    bool s;
    int i,j,d;
    while(!q.empty()) {
        tie(i,j,s,d) = q.front();
        q.pop();

        if(
            (j == g) ||
            (j == -1 && !s)
        ) continue;

        if(j == -1 || d < vis[i][j][s]) {
            if(j >= 0) vis[i][j][s] = d;
            if(j + 1 < g){
                q.emplace(i,j + 1,false,d + dist(
                    s ? hx[i] : gx[j],
                    s ? hy[i] : gy[j],
                    gx[j + 1],
                    gy[j + 1]
                ));
            }

            if(i + 1 < h) {
                q.emplace(i + 1,j,true,d + dist(
                    s ? hx[i] : gx[j],
                    s ? hy[i] : gy[j],
                    hx[i + 1],
                    hy[i + 1]
                ));
            }
        }
    }

    cout << vis[h - 1][g - 1][true];
}
