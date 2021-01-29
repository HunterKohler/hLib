#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
typedef tuple<int,int,int> edge;

#define lin(i,j) (((j) * (n + 1)) + (i))

vector<int> p;

int root(int u) {
    int v = u;
    while(p[v] != v)
        v = p[v];
    p[u] = v;
    return v;
}

bool join(int u, int v) {
    if(root(u) == root(v)) {
        return false;
    } else {
        p[root(u)] = root(v);
        return true;
    }
}

int main() {
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);

    int A,B,n,m;
    cin >> A >> B >> n >> m;

    vector<int> a(n), b(m);
    for(int& i: a) cin >> i;
    for(int& i: b) cin >> i;
    a.push_back(0);
    a.push_back(A);
    b.push_back(0);
    b.push_back(B);

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<edge> edge_list;

    for(int i = 0; i < n + 1; i++)
    for(int j = 0; j < m + 1; j++) {
        edge_list.emplace_back(lin(i,j), lin(i+1,j), b[j+1]-b[j]);
        edge_list.emplace_back(lin(i,j), lin(i,j+1), a[i+1]-a[i]);
    }

    sort(edge_list.begin(), edge_list.end(),
        [](const edge& a, const edge& b){
            return get<2>(a) < get<2>(b);
        });

    for(int i = 0; i < (n+1)*(m+1); i++)
        p.emplace_back(i);

    int u,v,w,sum = 0;
    for(edge& e: edge_list) {
        tie(u,v,w) = e;
        sum += join(u,v) * w;
        // if(join(u,v)) {
        //     c--;
        //     sum += w;
        //     cout << u << " " << v << " " << w << endl;
        // }
    }

    cout << sum;
}
