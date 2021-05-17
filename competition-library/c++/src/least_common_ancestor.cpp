#include <cmath>
#include <vector>

inline int ilog2(int x) {
    return std::log2(x) + 1;
}

class least_common_ancestor {
  public:
    int n;
    std::vector<int> euler, first, depth;
    // i'm not going to deal with array deconstruction and indexing in comp
    // so vectors idiot fuck
    std::vector<std::vector<int>> adj, spt;

    // total construction time is O(n+nlog(n)) = O(nlog(n))
    least_common_ancestor(std::vector<std::vector<int>> _adj, int _n):
        n{_n},
        adj{_adj},
        first(_n),
        euler(2*_n),
        depth(2*_n),
        spt(_n,std::vector<int>(ilog2(_n)+1)) {
        tour();

        // pre-processing on depth in range O(nlog(n))
        for(int i = 0; i < n; i++)
            spt[i][0] = depth[i];

        for(int j = 1; (1 << j) <= n; j++)
        for(int i = 0; i < n; i++)
            depth[i][j] = std::min(depth[i][j-1],depth[i+(1<<(j-1))][j-1])
    }

    // completing euler tour is O(n)
    void tour() {
        int index = 0;
        tour(0,-1,0,index);
    };

    void tour(int v, int f, int d, int& index) {
        euler[index] = v;
        first[index] = index;
        depth[index++] = d;
        for(int u: adj[v]) {
            if(u != f) {
                tour(u,v,d+1,index);
                euler[index] = v;
                depth[index++] = d;
            }
        }
    }

    int operator()(int u, int v) {
        return euler[rmq(first[u],first[v])];
    }
};
