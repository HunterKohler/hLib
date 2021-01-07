#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAXN 20

struct point { int x,y; };
point operator+(const point& p, const point& q) { return {p.x + q.x, p.y + q.y}; }
const point dP[] {{0,1},{1,0},{0,-1},{-1,0}};

int n;
char colors[MAXN][MAXN];
int _pcl[MAXN][MAXN][MAXN][MAXN]; // 0 == null , 1== false, 2 == true

inline bool in_grid(point p, point p0, point pf) {
    return p0.x <= p.x && p.x <= pf.x && p0.y <= p.y && p.y <= pf.x;
}

bool pcl(point p0, point pf) {
    if(_pcl[p0.x][p0.y][pf.x][pf.y])
        return _pcl[p0.x][p0.y][pf.x][pf.y] == 2;

    int counts[26] {0};
    bool vis[MAXN][MAXN] {false};

    point ip, iq;
    for(ip.x = p0.x; ip.x <= pf.x - 2; ip.x++)
    for(ip.y = p0.y; ip.y <= pf.y - 2; ip.y++) {
        for(iq.x = ip.x + 2; iq.x <= pf.x; iq.x++)
        for(iq.y = ip.y + 2; iq.y <= pf.y; iq.y++) {
            if(pcl(ip,iq)) {
                _pcl[p0.x][p0.y][pf.x][pf.y] = 1;
                return false;
            }
        }

        if(!vis[ip.x][ip.y]) {
            counts[colors[ip.x][ip.y] - 'A']++;

            queue<point> q;
            q.push(ip);

            while(!q.empty()) {
                point p = q.front();
                q.pop();

                for(point dp: dP) {
                    point p_n = p + dp;
                    if(in_grid(p_n, p0,pf) && colors[p_n.x][p_n.y] == colors[ip.x][ip.y]) {
                        q.push(p_n);
                    }
                }
            }
        }
    }

    int total_types;
    bool one = false, higher = false;
    for(char c: counts) {
        if(c == 1) {
            if(one) {
                _pcl[p0.x][p0.y][pf.x][pf.y] = 1;
                return false;
            }

            one = true;
        } else if(c > 1) {
            if(higher) {
                _pcl[p0.x][p0.y][pf.x][pf.y] = 1;
                return false;
            }

            higher = true;
        }
    }

    _pcl[p0.x][p0.y][pf.x][pf.y] = 2;
    return true;
}

int main() {
    freopen("where.in","r",stdin);
    freopen("where.out","w",stdout);

    cin >> n;
    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
        cin >> colors[i][j];

    int counter = 0;
    point p,q;
    for(p.x = 0; p.x < n - 2; p.x++)
    for(p.y = 0; p.y < n - 2; p.y++)
    for(q.x = p.x + 2; q.x < n; q.x++)
    for(q.y = p.y + 2; q.y < n; q.y++)
        counter += pcl(p,q);

    cout << counter;
}
