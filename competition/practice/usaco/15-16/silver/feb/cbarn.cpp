#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define nfor(i,n) for(int (i) = 0; (i) < (n); (i)++)
#define MAXN 1000

int N;

int main() {
    freopen("cbarn.in","r",stdin);
    freopen("cbarn.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scanf("%d", &N);

    vector<int> barn(N);
    nfor(i,N) {
        scanf("%d", &barn[i]);
    }

    int s {0};
    nfor(i,N) {
        int c {0};
        nfor(d,N) {
            int j = (i + d) % N;
            c += barn[j] - 1;
            if(c < 0) {
                break;
            } else if(j) {
                s = j;
                goto breaker;
            }
        }
    } breaker:

    rotate(barn.begin(), barn.begin() + s, barn.end());

    int sum {0};
    barn.push_back(0);
    vector<int> held(N + 1);
    nfor(i,N + 1) {
        held[i] = barn[i];

        if(i != 0)
        for(int j = 0; j <= i; j++) {
            if(held[j] > 0) {
                held[j]--;
                sum += (i - j) * (i - j);
                break;
            }
        }
    }

    printf("%d\n",sum);
}
