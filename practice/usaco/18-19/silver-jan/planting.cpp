#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 100000

int n;
int adj_count[MAXN];
int main() {
    freopen("planting.in", "r", stdin);
    freopen("planting.out", "w", stdout);

    cin >> n;
    for(int a,b; cin >> a >> b;) {
        adj_count[a-1]++;
        adj_count[b-1]++;
    }

    cout << *max_element(adj_count, adj_count+n) + 1;
}
