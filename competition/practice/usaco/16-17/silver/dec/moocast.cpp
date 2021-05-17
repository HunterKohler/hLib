#include <iostream>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

#define MAXN 200

int main() {
    freopen("moocast.in","r",stdin);
    freopen("moocast.out","w",stdout);

    int n;

    cin >> n;

    vector<int> adj[MAXN];
    int x[MAXN], y[MAXN], r[MAXN];
    for(int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> r[i];
        for(int j = 0; j < i; j++) {
            double d = hypot(x[j] - x[i], y[j] - y[i]);
            if(d <= r[j])
                adj[j].push_back(i);

            if(d <= r[i])
                adj[i].push_back(j);
        }
    }

    int vis_max = 0;
    bool vis[MAXN];
    for(int i = 0; i < n; i++) {
        fill_n(vis,n,false);
        queue<int> q;
        q.push(i);
        int vis_count = 0;
        while(!q.empty()) {
            int j = q.front();
            q.pop();
            if(!vis[j]) {
                vis[j] = true;
                vis_count++;
                for(int& k: adj[j]) {
                    q.push(k);
                }
            }
        }
        vis_max = max(vis_max,vis_count);
    }

    cout << vis_max;
}
