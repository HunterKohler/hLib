#ifndef LIB_ALGORITHMS_BIPARTITE_H_
#define LIB_ALGORITHMS_BIPARTITE_H_

// previously a member of competition-library

#include <vector>
#include <queue>

inline bool is_bipartite(const std::vector<std::vector<int>>& adj) {
    int n = adj.size();
    std::vector<bool> vis(n);
    std::vector<bool> color(n);
    std::queue<int> q({0});
    while(!q.empty()) {
        int i = q.front();
        q.pop();
        if(!vis[i]) {
            vis[i] = true;
            for(const int j: adj[i]) {
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

#endif
