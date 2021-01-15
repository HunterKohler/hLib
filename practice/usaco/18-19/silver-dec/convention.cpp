#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 100000

int n,m,c;
int t[MAXN];

int main() {
    freopen("convention.in", "r", stdin);
    freopen("convention.out", "w", stdout);

    cin >> n >> m >> c;
    for(int i = 0; i < n; i++)
        cin >> t[i];
    sort(t,t+n);

    int l = 0, r = t[n - 1];
    while(l + 1 < r) {
        int max_t = (l + r) / 2, i = 0, used = 0;
        while(i < n) {
            int j = i;
            while(j < n && (t[j] - t[i]) <= max_t && (j - i) < c) {
                j++;
            }
            i = j;
            used++;
        }

        if(used > m)
            l = (l + r) / 2;
        else
            r = (l + r) / 2;
    }

    cout << r;
}
