#include <iostream>

using namespace std;

#define INF (1 << 30)
#define MAXN 100000
#define MAXX 2000
#define endl '\n'

typedef pair<int,int> ipair;

int n;
int board[MAXX][MAXX];
bool synth[MAXX][MAXX];

int dx[] {-1,0,1,0};
int dy[] {0,-1,0,1};

int min_ans(int,int);
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    int total_synth = 0;
    for(int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;

        for(int i = 0; i < 4; i++)
            board[x+dx[i][y+dy[i]] += (!synth[x][y]);
        syth[x][y] = false;

        for(int i = 0; i < 4; i++) {
            if(board[x+dx[i]][y+dy[i]] == 3) {
                total_synth = min_ans(x+dx[i],y+dy[i]);
            }
        }
    }
}

int min_ans(int x, int y) {
    queue<pair<int,vector<pair<int,int>>>> q;
    q.insert({0,{x,y}});

    vector<pair<int,int>> v;
    while(true) {
        tie(a,v) = q.front();
        if(synt[a][b])

        q.pop();
    }
}
