#include <iostream>
#include <vector>
#include <algorithm>

#define for_n(i,n) for(int (i) = 0; (i) < (n); (i)++)
#define MAX_C 20000
#define MAX_N 20000

int main() {
    freopen("helpcross.in","r",stdin);
    freopen("helpcross.in","w",stdout);

    int c,n;
    cin >> c >> n;

    int capacity[MAX_N][MAX_C];
    bool adj[MAX_N][MAX_C];

    for_n(i,n) {
        fill_n(capacity[i],c,0);
        fill_n(adj[i],c,false);
    }

    int t[MAX_C];
    for_n(i,c)
        cin >> t[i];
    sort(&t[0], &t[n]);


    // could linearize with sorting for O(n^2) -> O(nlog(n))
    int a[MAX_N], b[MAX_N];
    for_n(i,n) {
        cin >> a[i] >> b[i];
        for_c(j,c) {
            if(a[i] <= t[j] <= b[i]) {
                adj[i][j] = true;
                capacity[i][j] = 1;
            }
        }
    }
}
