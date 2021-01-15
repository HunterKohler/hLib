#include <iostream>
#include <queue>

using namespace std;

#define MAXN 1000

int n,max_a = 0, min_p = 0;
bool ice[MAXN][MAXN], vis[MAXN][MAXN];
int main() {
    freopen("perimeter.in", "r", stdin);
    freopen("perimeter.out", "w", stdout);

    cin >> n;
    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++) {
        char c; cin >> c;
        ice[i][j] = (c == '#');
    }


    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++) {
        if(ice[i][j] && !vis[i][j]) {
            queue<pair<int,int>> q;
            q.emplace(i,j);

            int a = 0, p = 0;
            while(!q.empty()) {
                int x = q.front().first;
                int y = q.front().second;
                q.pop();

                if(!vis[x][y]) {
                    vis[x][y] = true;
                    a++;

                    for(auto dp: (pair<int,int>[]) {{0,1},{-1,0},{1,0},{0,-1}}) {
                        int x1 = x + dp.first;
                        int y1 = y + dp.second;

                        if(0 <= x1 && x1 < n && 0 <= y1 && y1 < n && ice[x1][y1])
                            q.emplace(x1,y1);
                        else
                            p++;

                    }
                }
            }

            if(a == max_a) {
                min_p = min(min_p, p);
            } else if(a > max_a) {
                max_a = a;
                min_p = p;
            }
        }
    }

    cout << max_a << " " << min_p;
}
