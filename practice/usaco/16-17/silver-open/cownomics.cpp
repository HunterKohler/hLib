#include <iostream>

#define MAXN 500
#define MAXM 50

int n,m;
char spot[MAXN][MAXM], reg[MAXN][MAXM];
int main() {
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);

    std::cin >> n >> m;
    for(auto& arr: {spot,reg})
    for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++) {
        std::cin >> arr[i][j];
        arr[i][j] -= 'A';
    }

    int counter = 0;
    for(int a = 0; a < m; a++)
    for(int b = a + 1; b < m; b++)
    for(int c = b + 1; c < m; c++) {
        bool vis[26][26][26] {};
        for(int i = 0; i < n; i++)
            vis [reg[i][a]]
                [reg[i][b]]
                [reg[i][c]] = true;
        for(int i = 0; i < n; i++) {
            if(vis [spot[i][a]]
                   [spot[i][b]]
                   [spot[i][c]]) break;
            if(i == n - 1) counter++;
        }
    } std::cout << counter;
}
