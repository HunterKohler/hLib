#include <iostream>
#include <cstdio>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

#define for_n(i,n) for(int (i) = 0; (i) < (n); (i)++)
#define has_switch(p) (switches.count(p))
#define is_lit(p) (lit[(p).x][(p).y])
#define in_grid(p) (0 <= (p).x && (p).x < N && 0 <= (p).y && (p).y < N)
#define light(p) (lit[(p).x][(p).y] = true)
#define is_recent(p) ((bool) rset.count(p))
#define MAXN 100

struct point {
    int x,y;
    point(int x0, int y0):
        x { x0 },
        y { y0 } {}
    point(): point(0,0) {}
};

bool operator==(point& p, point& q) {
    return p.x == q.x && p.y == q.y;
}

template <>
struct std::hash<point> {
    size_t operator()(const point& p) const {
        return (p.x + p.y + 1) * (p.x + p.y) / 2 + p.y;
    }
};

inline vector<point> adj_list(point& p) {

}

// ostream& operator<<(ostream& os, const point& p) {
//     os << "(" << p.x << "," << p.y << ")";
//     return os;
// }

int main() {
    freopen("lightson.in", "r", stdin);
    freopen("lightson.out", "w", stdout);
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    int N, M;
    unordered_map<point, vector<point>> switches;

    scanf("%d %d", &N, &M);
    for_n(i,M) {
        point p,q;
        scanf("%d %d %d %d",&p.x,&p.y,&q.x,&q.y);
        p.x--;p.y--;q.x--;q.y--;
        if(!has_switch(p))
            switches[p].insert({p,{q}});
        switches[p].push_back(q);
    }

    for_n(i,N) {
        fill_n(lit[0], N, false);
        fill_n(visited[0], N, false);
    } lit[0][0] = true;


    bool lit[MAXN][MAXN], visited[MAXN][MAXN];
    unordered_set<point> rset;
    queue<point> recent;

    while(!recent.empty()) {
        queue<point> next;

        while(!recent.empty()) {
            point& p = recent.front();
            for(point& q: adj_list(p)) {
                if((p.x == 0 && p.y == 0) || (in_range(q) && !is_recent(q) && is_lit(q))) {
                    next.push(p);
                    break;
                }
            }
            recent.pop();
        }

        while(!next.empty()) {
            point& p = next.front();

            if(!iss)

            next.pop();
        }
    }
}
