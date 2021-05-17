#include <cstdio>
#include <iostream>

using namespace std;

#define MAXN 100000

int main() {
    freopen("bcount.in","r",stdin);
    freopen("bcount.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N,Q;
    scanf("%d %d",&N,&Q);

    int R[MAXN + 1][3] = {{0,0,0}};
    for(int i = 1; i <= N; i++){
        R[i][0] = R[i - 1][0];
        R[i][1] = R[i - 1][1];
        R[i][2] = R[i - 1][2];
        int t;
        scanf("%d",&t);
        R[i][t - 1]++;
    }

    for(int i = 0; i < Q; i++) {
        int a,b;
        scanf("%d %d",&a,&b);
        printf("%d %d %d\n",
            R[b][0] - R[a - 1][0],
            R[b][1] - R[a - 1][1],
            R[b][2] - R[a - 1][2]
        );
    }
}
