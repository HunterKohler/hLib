#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#define MAXN 50000

void print_arr(int *arr, int n) {
    cout << "arr:" << endl;
    for(int i = 0; i < n; i++) {
        cout << "\t" << i <<": " << *(arr + i) <<endl;
    }
}

int main() {
    freopen("highcard.in","r",stdin);
    freopen("highcard.out","w",stdout);
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);


    int N;
    scanf("%d",&N);

    int E[MAXN], B[MAXN];
    bool used[2 * MAXN];
    for(int i = 0; i < N; i++) {
        scanf("%d",&E[i]);
        used[--E[i]] = true;
    }

    {
        int i = 0;
        for(int j = 0; j < N * 2; j++) {
            if(!used[j])
                B[i++] = j;
        }
    }

    sort(&E[0],&E[N]);
    sort(&B[0],&B[N]);

    int p = 0;
    for(int *e = &E[0], *b = &B[0]; e != &E[N]; e++) {
        while(true) {
            if(b == &B[N]) {
                goto out;
            } else if(*b > *e) {
                b++;
                p++;
                break;
            } else {
                b++;
            }
        }
    }

    out:
    cout << p;
}
