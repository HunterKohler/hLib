#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;
typedef long long ll;
typedef pair<int,int> ipair;

#define MAXN 1000

ostream& operator<<(ostream& os, const ipair& p) {
    return os << "(" << p.first << "," << p.second << ")";
}

int n,m;
int fx,fy,bx,by;
map<char,int> dx {{'N',0},{'E',1},{'S',0},{'W',-1}};
map<char,int> dy {{'N',1},{'E',0},{'S',-1},{'W',0}};
vector<ipair> v;
vector<ipair> u;
vector<vector<ll>> dist;

ll min(ll a, ll b, ll c) {
    if(a <= b && a <= c)
        return a;
    if(b <= a && b <= c)
        return b;
    else
        return c;
}

int mem[MAXN+1][MAXN+1];
bool vis[MAXN+1][MAXN+1];
ll min_cost(int x, int y) {
    if(x == 0 && y == 0)
        return 0;
    else if(x < 0 || y < 0)
        return (1ll << 60);
    if(!vis[x][y]) {
        vis[x][y] = true;
        mem[x][y] = min(
            min_cost(x-1,y),
            min_cost(x,y-1),
            min_cost(x-1,y-1)
        ) + dist[x][y];
    }

    return mem[x][y];
}

int main() {
    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);


    cin >> n >> m;
    cin >> fx >> fy
        >> bx >> by;

    v.emplace_back(fx,fy);
    u.emplace_back(bx,by);

    for(int i = 0; i < n; i++) {
        char c;
        cin >> c;
        v.emplace_back(
            v[i].first + dx[c],
            v[i].second + dy[c]
        );
    }

    for(int i = 0; i < m; i++) {
        char c;
        cin >> c;
        u.emplace_back(
            u[i].first + dx[c],
            u[i].second + dy[c]
        );
    }

    for(ipair& p: v) {
        dist.emplace_back();
        for(ipair& q: u) {
            dist.back().push_back(
                pow(q.first - p.first,2) + pow(q.second - p.second,2)
            );
        }
    }

    cout << min_cost(n, m);
}
