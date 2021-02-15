#include <iostream>
#include <vector>

using namespace std;

#define MAXN 100000

int n;
int a[MAXN], vis[MAXN], loops[MAXN];

int main() {
    freopen("shuffle.in", "r", stdin);
    freopen("shuffle.out", "w", stdout);

    cin >> n;
    for(int i = 0; i < n; i++)
        (cin >> a[i], a[i]--);

    for(int i = 0; i < n; i++) {
        vector<int> order;

        int j = i;
        for(;!vis[j]; j = a[j]) {
            vis[j] = true;
             order.push_back(j);
        }

        if(i == j) {
            for(int x: order)
                loops[x] = true;
        } else {
            bool state = false;
            for(int k = 0; k < order.size(); k++) {
                if(order[k] == j)
                    state = true;

                loops[order[k]] = state;
            }
        }
    }

    int total = 0;
    for(int i = 0; i < n; i++)
        total += loops[i];
    cout << total;
}
