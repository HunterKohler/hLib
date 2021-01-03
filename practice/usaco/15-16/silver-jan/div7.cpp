#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    freopen("div7.in","r",stdin);
    freopen("div7.out","w",stdout);

    int n;
    cin >> n;

    int start[7];
    fill_n(start,7,-1);

    int x, high = -1;
    for(int i = 0; i < n; i++) {
        cin >> x;
        x %= 7;

        if(start[x] == -1)
            start[x] = i;

        rotate(&start[0], &start[x], &start[7]);

        if(start[0] != -1)
            high = max(high, i - start[0]);
    }

    cout << high;
}
