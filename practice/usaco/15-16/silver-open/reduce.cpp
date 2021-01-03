#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

#define nfor(i,n) for(int (i) = 0; (i) < (n); (i)++)
#define INF (1 << 30)
#define MAXN ((int) 5e4)

int find_min();
int find_min(vector<int> vect);

struct point {
    int i;
    void print() {
        printf("(%d,%d)\n", x, y);
    }
};

int N;
int x[MAXN], y[MAXN], sx[MAXN], sy[MAXN];

int main() {
    freopen("reduce.in","r",stdin);
    freopen("reduce.out","w",stdout);
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    scanf("%d", &N);
    nfor(i,N) {
        scanf("%d %d", &x[i], &y[i]);
        sx[i] = cy[i] = i;
    }

    sort(&sx[0], &sx[N],
        [](int i, int j) {
            return x[i] < x[j];
        });

    sort(&sy[0], &sy[N],
        [](int i, int j) {
            return y[i] < y[j];
        });

    cout << x[sx[0]] << endl;
    cout << x[sx[1]] << endl;
    cout << x[sx[2]] << endl;

    gen({0,0,0,0});
}

int minA {0};
