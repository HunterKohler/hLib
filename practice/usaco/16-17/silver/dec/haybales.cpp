#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 100000

int main() {
    freopen("haybales.in","r",stdin);
    freopen("haybales.out","w",stdout);

    int n,q;
    cin >> n >> q;

    int x[MAXN];
    for(int i = 0; i < n; i++)
        cin >> x[i];

    sort(&x[0],&x[n]);

    for(;q > 0;q--) {
        int a, b;
        cin >> a >> b;

        cout << (
            upper_bound(&x[0],&x[n],b) -
            lower_bound(&x[0],&x[n],a)
        ) << endl;
    }
}
