#include <iostream>
#include <vector>
#include <tuple>

using namespace std;
typedef pair<int,int> ipair;

#define MAXN 1000

int n;
int a[MAXN][MAXN];
bool on[MAXN][MAXN];
vector<ipair> grid;

bool in_grid(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

int main() {
    freopen("spaced.in", "r", stdin);
    freopen("spaced.out", "w", stdout);

    cin >> n;
    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++) {
        cin >> a[i][j];
        on[i][j] = (i % 2);
        grid.emplace_back(i,j);
    }

    sort(grid.begin(), grid.end(),
        [](const ipair& p, const ipair& q) {
            return a[p.first][p.second] > a[q.first][q.second];
        });

    int s = 0;
    for(ipair p: grid) {
        int x,y;
        tie(x,y) = p;
        bool valid = (
            (!in_grid(x-1,y-1) || (
                (on[x-1][y] + on[x][y-1] + on[x-1][y-1]) < 2
            )) &&
            (!in_grid(x-1,y+1) || (
                (on[x-1][y] + on[x][y+1] + on[x-1][y+1]) < 2
            )) &&
            (!in_grid(x+1,y-1) || (
                (on[x+1][y] + on[x][y-1] + on[x+1][y-1]) < 2
            )) &&
            (!in_grid(x+1,y+1) || (
                (on[x+1][y] + on[x][y+1] + on[x+1][y+1]) < 2
            ))
        );

        if(valid) {
            on[x][y] = true;
            s += a[x][y];
        }
    }

    cout << s;
}
