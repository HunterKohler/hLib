#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

#define MAXN ((int) 1e5)

int n;
int a[MAXN],b[MAXN];

// inline long long min(int a, int b, int c) { return min(a,min(b,c)); }
// long long dist(int y) {
//     long long d = 0;
//     for(int i = 0; i < n; i++) {
//         d += min(
//             abs(a[i] - b[i]),
//             abs(y - a[i]) + abs(b[i]),
//             abs(a[i]) + abs(y - b[i])
//         );
//     }
//
//     return d;
}

int main() {
    freopen("teleport.in", "r", stdin);
    freopen("teleport.out", "w", stdout);

    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i] >> b[i];
}
