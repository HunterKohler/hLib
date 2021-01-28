#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define FORN(i,n) for(int (i) = 0; (i) < (n) ; (i)++)
#define INF (1 << 30)
#define MAXN 1000

struct cow { int x,y; };

int N;
cow cows[MAXN];
cow *cows_x[MAXN], *cows_y[MAXN];

int main() {
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scanf("%d", &N);
    FORN(i,N) {
        scanf("%d %d", &cows[i].x, &cows[i].y);
        cows_x[i] = &cows[i];
        cows_y[i] = &cows[i];
    }

    sort(begin(cows_x), begin(cows_x) + N,
        [](const cow *a, const cow *b) {
            return a->x < b->x;
        });

    sort(begin(cows_y), begin(cows_y) + N,
        [](const cow *a, const cow *b) {
            return a->y < b->y;
        });

    int i {0}, M {INF};
    FORN(i,N) if(i == N - 1 || cows_x[i]->x != cows_x[i + 1]->x) {
        int j{0}, ul {i}, ur {N - i}, ll {0}, lr {0};
        FORN(j,N) {
            if(cows_y[j]->x >= cows_x[i]->x) { lr++; ur--; }
            else { ll++ ; ul--; }

            if(j == N - 1 || cows_y[j]->y != cows_y[j + 1]->y) {
                M = min(M, max( max(ul,ur), max(ll,lr) ));
            }
        }
    }

    printf("%d", M);
}
