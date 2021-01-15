#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#define MAXN 100000

struct event {
    bool is_arrival;
    int etime, cow;
    event(bool _ia, int _t, int _c):
        is_arrival {_ia},
        etime {_t},
        cow {_c} { }
    void print() const {
        printf("{is_arrival: %s, time: %d, cow: %d}\n",
            is_arrival ? "true" : "false", etime, cow);
    }
};

struct comp {
    bool operator()(const event& e1, const event& e2) {
        if(e1.etime == e2.etime) {
            if(!e1.is_arrival)
                return false;
            else if(!e2.is_arrival)
                return true;
            return e1.cow > e2.cow;
        }

        return e1.etime > e2.etime;
    }
};



int n;
int a[MAXN], t[MAXN];
priority_queue<event,vector<event>,comp> pq;
int main() {
    freopen("convention2.in", "r", stdin);
    freopen("convention2.out", "w", stdout);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i] >> t[i];
        pq.emplace(true, a[i], i);
    }

    int max_wait = 0;
    bool taken = false;
    priority_queue<int,vector<int>,greater<int>> wait;
    while(!pq.empty() || !wait.empty()) {
        int etime = pq.top().etime;
        if(!pq.empty()) {
            while(!pq.empty() && pq.top().etime == etime) {
                if(pq.top().is_arrival)
                    wait.push(pq.top().cow);
                else
                    taken = false;
                pq.pop();
            }
        }

        if(!taken && !wait.empty()) {
            taken = true;
            max_wait = max(max_wait, etime - a[wait.top()]);
            pq.emplace(false,etime + t[wait.top()],wait.top());
            wait.pop();
        }
    }

    cout << max_wait;
}
