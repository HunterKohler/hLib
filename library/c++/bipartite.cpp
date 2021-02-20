#include <vector>
#include <queue>

#include "bipartite.h"

// untested
bool is_bipartide(const vector<int>& adj) {
    int n = adj.size();
    vector<bool> vis(n);
    vector<bool> color(n);
    queue<int> q;
    q.push(adj[0]);
    while(!q.empty()) {
        int i = q.pop();
        if(!vis[i]) {
            vis[i] = true;
            for(int j: adj[i]) {
                if(vis[j] && color[i] == color[j]) {
                    return false;
                } else if(!vis[j]) {
                    color[j] = !color[i];
                    q.push(j);
                }
            }
        }
    }
    return true;
}

int main() {}
