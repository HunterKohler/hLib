#include <iostream>
#include <queue>

using namespace std;

#define MAXN 100000

struct point {
    int i,x;
    bool left;
    point(int _i,int _x, bool _l):
        i{_i},x{_x},left{_l} {}
    bool operator<(const point& p) const {
        return x > p.x;
    }
};

int n;
priority_queue<point> q;
int main() {
    freopen("mountains.in", "r", stdin);
    freopen("mountains.out", "w", stdout);

    cin >> n;
    for(int i = 0; i < n; i++) {
        int x,y; cin >> x >> y;
        q.emplace(i,x - y,true);
        q.emplace(i,x + y,false);
    }

    int peaks = n;
    vector<int> open;
    while(!q.empty()) {
        point p = q.top();
        // cout << p.i << (p.left ? " left at " : " right at ") << p.x << endl;
        q.pop();
        if(p.left) { // could bsearch for this by knowing x by i
            open.push_back(p.i);
        } else {
            if(open[0] != p.i) {
                peaks--;
            }

            for(int j = 0; j < open.size(); j++) {
                if(open[j] == p.i) {
                    open.erase(open.begin() + j);
                    break;
                }
            }
        }
    }

    cout << peaks;
}
