#include <iostream>
#include <queue>
#include <tuple>
#include <cmath>

using namespace std;

#define MAXN 1000

int n;
int a[MAXN], b[MAXN];
int vis[MAXN][MAXN];

int main() {
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);

    cin >> n;
    for(int *x: {a,b})
    for(int i = 0; i < n; i++)
        cin >> x[i];

    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
        vis[i][j] = -1;

    queue<tuple<int,int,int>> q;
    q.emplace();

    int m = 0;
    while(!q.empty()) {
        int i,j,t;
        tie(i,j,t) = q.front();
        q.pop();

        // printf("(%d,%d,%d)\n",i,j,t);
        if(i >= n || j >= n) {
            m = max(m,t);
        } else if(t > vis[i][j]) {
            vis[i][j] = t;
            if(abs(a[i] - b[j]) <= 4)
                q.emplace(i + 1, j + 1, t + 1);
            q.emplace(i + 1, j, t);
            q.emplace(i, j + 1, t);
        }
    }

    cout << m;
}
