#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;
typedef tuple<int,int,int> edge;

#define for_n(i,n) for(int (i) = 0; (i) < (n); (i)++)

int A,B,n,m;
vector<int> a,b;
vector<edge> e;

int lin(int i, int j) {
    return i + j * (n + 1);
}

struct disjoint_set {
    vector<int> p;
    disjoint_set(int s) {
        for(int i = 0; i < s; i++)
            p.push_back(i);
    }
    int root(int u) {
        return u == p[u] ? u : p[u] = root(p[u]);
    }
    bool join(int u, int v) {
        if(root(u) == root(v))
            return false;
        else {
            p[root(u)] = root(v);
            return true;
        }
    }
};

int main() {
    !freopen("fencedin.in", "r", stdin);
    !freopen("fencedin.out", "w", stdout);

    cin >> A >> B >> n >> m;

    a = {0,A};
    b = {0,B};

    int a_i,b_j;
    for_n(i,n) {
        cin >> a_i;
        a.push_back(a_i);
    }
    for_n(j,m) {
        cin >> b_j;
        b.push_back(b_j);
    }

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

    for_n(i,n) for_n(j,m + 1)
        e.emplace_back(lin(i,j),lin(i + 1,j),b[j + 1] - b[j]);
    for_n(i,n + 1) for_n(j,m)
        e.emplace_back(lin(i,j),lin(i,j + 1),a[i + 1] - a[i]);

    sort(e.begin(),e.end(),
        [](const edge& e1, const edge& e2) {
            return get<2>(e1) < get<2>(e2);
        });

    disjoint_set d((n + 1) * (m + 1));
    int u,v,w,sum = 0;
    for(edge& e_i: e) {
        tie(u,v,w) = e_i;
        sum += w * d.join(u,v);
    }

    cout << sum;
}
