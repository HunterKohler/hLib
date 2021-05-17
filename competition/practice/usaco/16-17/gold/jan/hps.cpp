#include <iostream>

using namespace std;

#define MAXN 100000
#define MAXK 20


enum { H,P,S };

bool beats(int i, int j) {
    return (i == H && j == S) || (i == S && j == P) || (i == P && j == H);
}

int n,k;
int g[MAXN];
int w[MAXN][MAXK][3];
int wins(int i,int k_res,int g_curr) {
    int& m = w[i][k_res][g_curr];
    if(i == 0) return beats(g_curr,g[i]);

    if(m == -1) {
        m = beats(g_curr,g[i]) + max(
            max(
                wins(i - 1, k_res, g_curr),
                wins(i - 1, k_res - 1, P)
            ),
            max(
                wins(i - 1, k_res - 1, H),
                wins(i - 1, k_res - 1, S)
            )
        );
    }

    return m;
}

int main() {
    !freopen("hps.in", "r", stdin);
    !freopen("hps.out", "w", stdout);

    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if(c == 'H') g[i] = H;
        if(c == 'P') g[i] = P;
        if(c == 'S') g[i] = S;

        for(int j = 0; j < k; j++)
        for(int r: {H,P,S})
            w[i][j][r] = -1;
    }

    cout << max(
        wins(n-1,k,H),
        max(
            wins(n-1,k,P),
            wins(n-1,k,S)
        )
    );

}
