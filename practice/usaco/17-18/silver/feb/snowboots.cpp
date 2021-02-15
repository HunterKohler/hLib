#include <iostream>
#include <queue>
#include <utility>

using namespace std;

#define MAXN 250

int n,b;
int f[MAXN], s[MAXN], d[MAXN];
bool vis[MAXN][MAXN];

int main() {
    freopen("snowboots.in", "r", stdin);
    freopen("snowboots.out", "w", stdout);

    cin >> n >> b;
    for(int i = 0; i < n; i++)
        cin >> f[i];
    for(int i = 0; i < b; i++)
        cin >> s[i] >> d[i];

    queue<pair<int,int>> q;
    q.emplace(0,0);

    while(!q.empty()) {
        int i = q.front().first;
        int j = q.front().second;
        q.pop();

        if(i < n && j < b && !vis[i][j]) {
            vis[i][j] = true;

            for(int k = i + 1; k < min(n,i + d[j] + 1); k++) {
                if(f[k] < s[j])
                    q.emplace(k,j);
            }

            while(++j < b) {
                if(s[j] >= f[i])
                    q.emplace(i,j);
            }
        }
    }

    for(int i = 0; i < b; i++) {
        if(vis[n - 1][i]) {
            cout << i << endl;
            break;
        }
    }
}
