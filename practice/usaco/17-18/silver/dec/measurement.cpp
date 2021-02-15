#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

struct entry { int day, id, delta; };

int main() {
    freopen("measurement.in", "r", stdin);
    freopen("measurement.out", "w", stdout);

    int n,g;
    cin >> n >> g;

    map<int,int> cows;
    map<int,set<int>> levels;
    vector<entry> entries(n);

    levels[g] = {-1};
    cows[-1] = g;

    for(entry& e: entries) {
        cin >> e.day >> e.id >> e.delta;
        cows[e.id] = g;
        levels[g].insert(e.id);
    }

    sort(entries.begin(), entries.end(),
        [](const entry& a, const entry& b) {
            return a.day < b.day;
        });

    int total = 0;
    for(entry& e: entries) {
        int l_i = cows[e.id],
            l_f = (cows[e.id] += e.delta),
            top = (--levels.end())->first;

        levels[l_i].erase(e.id);
        levels[l_f].insert(e.id);

        if(levels[l_i].size() == 0)
            levels.erase(l_i);

        total +=
            (l_i == top && l_f < top && (
                (--levels.end())->first != l_f ||
                levels[l_f].size() > 1 )) ||
            (l_i < top && l_f >= top) ||
            (l_i == top && l_f > top && levels.count(l_i));
    }

    cout << total;
}
