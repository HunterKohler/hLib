#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define INF (1 << 30)
#define MAXN 100000

int n;
int x[MAXN];

int main() {
    freopen("herding.in", "r", stdin);
    freopen("herding.out", "w", stdout);

    cin >> n;

    for(int i = 0; i < n; i++)
        cin >> x[i];
    sort(x,x + n);

    if(n == 2) {
        if(x[0] + 1 == x[1])
            cout << 0 << endl << 0;
        else
            cout << 1 << endl << 1;
        return 0;
    }

    int _min = INF;
    for(int i = 0; i < n; i++) {
        int j = upper_bound(x, x + n, x[i] + n -1) - x;
        _min = min(_min, (n - (j - i)));
    }

    cout << _min << endl;

    int _max = max(x[1]-x[0],x[n-1]-x[n-2])-1;
    for(int i = 1; i < n - 2; i++)
        _max += x[i+1]-x[i]-1;
    cout << _max;
}
