#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

#define MAXN 100
#define for_n(i,n) for(int (i) = 0; (i) < (n); (i)++)

struct point {
    int x,y;
    point(int a, int b): x{a},y{b} {}
    point(): point(0,0) {}
};

int n,m;
vector<point> S[MAXN][MAXN];
vector<point> delta {{0,1},{0,-1},{1,0},{-1,0}};

bool in_grid(point& p) {
    return 0 <= p.x && p.x < n && 0 <= p.y && p.y < n;
}

ostream& operator<<(ostream& os, const point& p) {
    os << p.x << " " << p.y;
    return os;
}

int main() {
    freopen("lightson.in","r",stdin);
    freopen("lightson.out","w",stdout);

    cin >> n >> m;
    for_n(i,m) {
        int x,y,a,b;
        cin >> x >> y >> a >> b;
        S[x - 1][y - 1].emplace_back(a - 1,b - 1);
    }

    bool vis[MAXN][MAXN], lit[MAXN][MAXN];
    for_n(i,n) {
        fill_n(lit[i],n,false);
        fill_n(vis[i],n,false);
    } lit[0][0] = true;

    vector<point> next;
    next.emplace_back();

    bool first = true;
    while(!next.empty()) {
        queue<point> q;
        if(first) {
            first = false;
            q.emplace();
        };

        for(point& p: next) {
            lit[p.x][p.y] = true;
            for(point& dp: delta) {
                point adj {p.x + dp.x, p.y + dp.y};
                if(in_grid(adj) && vis[adj.x][adj.y]) {
                    q.push(p);
                    break;
                }
            }
        } next.clear();

        while(!q.empty()) {
            point p = q.front();
            q.pop();

            if(!vis[p.x][p.y]) {
                vis[p.x][p.y] = true;

                for(point& s: S[p.x][p.y])
                    next.push_back(s);

                for(point& dp: delta) {
                    point adj {p.x + dp.x, p.y + dp.y};
                    if(in_grid(adj) && lit[adj.x][adj.y] && !vis[adj.x][adj.y]) {
                        q.push(adj);
                    }
                }
            }
        }
    }

    int total { 0 };
    for_n(i,n) for_n(j,n) if(lit[i][j]) total   ++;
    cout << total;
}
