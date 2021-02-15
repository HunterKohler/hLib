#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct event { bool s; int t, i; };

int main() {
    freopen("lifeguards.in", "r", stdin);
    freopen("lifeguards.out", "w", stdout);

    int n;
    cin >> n;

    vector<event> events;
    for(int i = 0; i < n; i++) {
        int t0,tf;
        cin >> t0 >> tf;
        events.push_back({true,t0,i});
        events.push_back({false,tf,i});
    }

    sort(events.begin(), events.end(),
        [](const event& a, const event& b){
            return a.t < b.t;
        });

    vector<int> alone(n);
    set<int> guards {events[0].i};

    int sum = 0;
    for(int i = 1; i < events.size(); i++) {
        event &a = events[i - 1], &b = events[i];

        int dt = b.t - a.t;

        if(guards.size() == 1)
            alone[*guards.begin()] += dt;

        if(guards.size() > 0)
            sum += dt;

        if(b.s)
            guards.insert(b.i);
        else
            guards.erase(b.i);
    }

    int _min = (1 << 30);
    for(int i: alone)
        _min = min(_min,i);

    cout << (sum - _min);
}
