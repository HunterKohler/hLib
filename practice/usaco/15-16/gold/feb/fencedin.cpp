#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;

#define MAXN 2010

int n,m;
ll a[MAXN+2],b[MAXN+2];

int main() {
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);

    // a[0] = b[0] = 0;
    cin >> a[1] >> b[1] >> n >> m;
    for(int i = 0; i < n; i++)
        cin >> a[2+i];
    for(int i = 0; i < m; i++)
        cin >> b[2+i];

    sort(a, a+n+2);
    sort(b, b+n+2);

    ll _min = (1ll << 60);
    for(int i = 0; i < n+1; i++) {
        _min = min(_min, abs(a[i+1] - a[i]));
        cout << abs(a[i+1] - a[i]) << endl;
    }
    for(int i = 0; i < m+1; i++) {
        _min = min(_min, abs(b[i+1] - b[i]));
        cout << abs(b[i+1] - b[i]) << endl;
    }

    cout << _min;
}
