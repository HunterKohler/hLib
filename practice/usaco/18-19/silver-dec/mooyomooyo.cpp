#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAXN 100

int n,m = 10,k;
int board[10][MAXN];

int main() {
    freopen("mooyomooyo.in", "r", stdin);
    freopen("mooyomooyo.out", "w", stdout);

    cin >> n >> k;
    for(int j = n - 1; j >= 0; j--)
    for(int i = 0; i < m; i++) {
        char c;
        cin >> c;
        board[i][j] = c - '0';
    }

    bool change = true;
    while(change) {
        change = false;
        bool vis[MAXN][MAXN] {};
        for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++) {
            if(!board[i][j] || vis[i][j])
                continue;

            queue<pair<int,int>> q;
            vector<pair<int,int>> r;
            q.emplace(i,j);

            while(!q.empty()) {
                int x = q.front().first;
                int y = q.front().second;
                q.pop();

                if(!vis[x][y]) {
                    vis[x][y] = true;
                    r.emplace_back(x,y);

                    for(pair<int,int> dp: (pair<int,int>[]){{0,1},{1,0},{-1,0},{0,-1}}) {
                        int x1 = x + dp.first;
                        int y1 = y + dp.second;

                        if(0 <= x1 && x1 < m && 0 <= y1 && y1 < n && board[x][y] == board[x1][y1])
                            q.emplace(x1,y1);
                    }
                }
            }


            if(r.size() >= k) {
                change = true;
                for(pair<int,int>& p: r)
                    board[p.first][p.second] = 0;
            }

        }

        for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
        for(int y = j; y < n; y++) {
            if(board[i][y]) {
                board[i][j] = board[i][y];
                if(y != j)
                    board[i][y] = 0;
                break;
            }
        }
    }

    for(int j = n - 1; j >= 0; j--) {
        for(int i = 0; i < m; i++)
                cout << board[i][j];
        cout << endl;
    }
}
