#include <iostream>
#include <set>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

#define INF (1 << 30)
#define MAXN 200000

// template <>
// struct std::hash<pair<int,int>> {
//     size_t operator()(const pair<int,int>& p) {
//         return (p.first + p.second) * (p.first + p.second + 1) / p.second + 1;
//     }
// };

int main() {
    // freopen("dance.in", "r", stdin);
    // freopen("dance.out", "w", stdout);

    int n,k;
    cin >> n >> k;

    vector<vector<pair<int,int>>> moves(n); // pair (time, next)
    for(int i = 0; i < k; i++) {
        int a,b;
        cin >> a >> b;

        moves[a-1].emplace_back(i,b-1);
        moves[b-1].emplace_back(i,a-1);
    }

    for(int i = 0; i < n; i++) {
        sort(moves[i].begin(), moves[i].end());
    }

    // for(int i = 0; i < n; i++) {
    //     printf("moves[%d]:\n", i);
    //     for(pair<int, int> p: moves[i])
    //         printf("    (%d,%d)\n",p.first,p.second);
    // } printf("\n");

    for(int i = 0; i < n; i++) {
        // printf("start at %d \n", i);
        set<int> vis_index;
        set<pair<int,int>> vis;
        int t = 0, j = i;
        while(!vis.count({t,j})) {
            vis.emplace(t,j);
            vis_index.emplace(j);
            if(moves[j].size() == 0)
                break;
            if(moves[j].back().first < t)
                t = 0;

            auto next = lower_bound(
                moves[j].begin(),
                moves[j].end(),
                pair<int,int>(t,-INF)
            );

            // printf(
            //     "\tmove from %d to %d at %d\n",
            //     j,
            //     next->second,
            //     next->first
            // );

            tie(t,j) = *next;
            t++;
        }

        // for(int i: vis_index)
        //     cout << i << " ";
        // cout << endl;

        cout << vis_index.size() << endl;
    }
}
