#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define MAXN ((int) 5e4)

int N,K;
int D[MAXN];

void print(int *arr, int size) {
    cout << "[";
    for(int i = 0; i < size; i++) {
        cout << *(arr+i);
        if(i != size - 1)
            cout << ",";
    }
    cout << "]" << endl;
};

int main() {
    freopen("diamond.in","r",stdin);
    freopen("diamond.out","w",stdout);
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    scanf("%d %d", &N, &K);
    for(int i = 0; i < N; i++) {
        scanf("%d", &D[i]);
    }

    // cout << "N: " << N << endl;
    // cout << "K: " << K << endl;

    sort(begin(D), begin(D) + N);

    // cout << "D: "; print(D,N);

    int ranges[MAXN];
    for(int i = 0; i < N; i++) {
        ranges[i] = (upper_bound(
            begin(D) + i,
            begin(D) + N,
            D[i] + K
        ) - begin(D)) - i;
    }

    // cout << "ranges: "; print(ranges, N);

    int ans = 0;
    for(int i = 0; i < N; i++) {
        ans = max(ans, ranges[i] + *max_element(
            begin(ranges) + i + ranges[i],
            begin(ranges) + N
        ));
    }

    printf("%d\n",ans);
}
