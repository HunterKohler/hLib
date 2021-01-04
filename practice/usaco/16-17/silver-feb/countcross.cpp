#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct point {
    int x,y;
    point(int a,int b): x{a}, y{b} {}
    point(): point(0,0) {}
    point operator+(const point& p) const {
        return {x + p.x,y + p.y};
    }
};

const vector<point> Dp {{0,1},{1,0},{0,-1},{-1,0}};
bool operator==(const point& p, const point& q) {
    return p.x == q.x && p.y == q.y;
}

namespace std {
    template <>
    struct hash<point> {
        size_t operator()(const point &p) const {
            return (p.x + p.y + 1) * (p.x + p.y) / 2 + p.y;
        }
    };
}

int n,k,r;
unordered_map<point,unordered_set<point>> roads;

inline bool in_grid(int x, int y) { return 0 <= x && x < n && 0 <= y && y < n; }
inline bool in_grid(point& p){ return in_grid(p.x,p.y); }
bool is_adj(point p1, point p2) {
    return
        in_grid(p1) &&
        in_grid(p2) && (
            !roads.count(p1) ||
            !roads[p1].count(p2)
        ) && (
            !roads.count(p2) ||
            !roads[p2].count(p1)
        );
}

int main() {
    freopen("countcross.in","r",stdin);
    freopen("countcross.out","w",stdout);

    cin >> n >> k >> r;

    for(int i = 0; i < r; i++) {
        point v,u;
        cin >> v.x >> v.y >> u.x >> u.y;
        v.x--;v.y--;u.x--;u.y--;
        if(roads.count(v)) roads[v].insert(u);
        else roads.insert({v,{u}});
        if(roads.count(u)) roads[u].insert(v);
        else roads.insert({u,{v}});
    }

    vector<point> cows(k);
    for(point& cow: cows) {
        cin >> cow.x >> cow.y;
        cow.x--; cow.y--;
    }


    int i_color = 0;
    vector<int> counts;
    vector<vector<int>> color(n,vector<int>(n,-1));
    for(point cow: cows) {
        if(color[cow.x][cow.y] == -1) {
            queue<point> q;
            q.push(cow);

            while(!q.empty()) {
                point p = q.front();
                q.pop();

                if(color[p.x][p.y] == -1) {
                    color[p.x][p.y] = i_color;

                    for(const point& dp: Dp)
                        if(is_adj(p,p + dp))
                            q.push(p + dp);
                }
            }

            counts.push_back(1);
            i_color++;
        } else counts[color[cow.x][cow.y]]++;
    }

    int pairs = 0;
    for(int i: counts)
        pairs += i * (k - i);

    cout << (pairs >> 1) << endl;
}
