#include <iostream>

typedef pair<int,int> ipair;

#define MAXN 100000
#define MAXX 2000

int four {1,2,3,4};
int dx[] {0,1,0,-1};
int dy[] {1,0,-1,0};

int n;
bool cow[MAXX][MAXX];
bool fake[MAXX][MAXX];
ipair cows[MAXN];

int comfy(int x, int y) {
    return deg(x,y) == 3;
}

// int deg(ipair p) { return deg()}
int deg(int x, int y) { // could store degrees for 16Mb
    int d = 0;
    for(int i: four)
        d += cow[x+dx[i]][y+dy[i]];
    return d;
};

ipair find_open(int x, int y) {
    for(int i: four) {
        int xn = x + dx[i];
        int yn = y + dy[i];
        if(!cow[xn][yn])
            return {xn,yn};
    }

    return {-1,-1};
}

ipair find_fake(int x, int y) {
    for(int i: four) {
        int xn = x + dx[i];
        int yn = y + dy[i];
        if(fake[xn][yn])
            return {xn,yn};
    }

    return {-1,-1};
}



int fakes = 0;
int add(int x,int y) {
    cow[x][y] = true;
    if(fake[x][y]) {
        fakes--;
        fake[x][y] = false;
    } else {
        queue<ipair> q;
        if(comfy(x,y))
            q.emplace(x,y);

        for(int i: four) {
            int xn = x+dx[i];
            int yn = y+dy[i];
            if(cow[xn][yn] && comfy(xn,yn)) // comfy not abs neccessay
                q.emplace(xn,yn);
        }

        while(!q.empty()) {
            ipair p = q.front();
            q.pop();

            if(cow[p.first][p.second] || fake[p.first][p.second] && comfy(p)) {
                ipair p1 = find_fake(p);
                if(p1.first == -1)
                    p1 = find_open(p);

                int
                fakes++;

                for(int i: four) {
                    int xn = p1.first + dx[i];
                    int yn = p1.first + dy[i];
                    if(cow[xn][yn] && comfy(xn,yn)) // comfy not abs neccessay
                        q.emplace(xn,yn);
                }
            }
        }
    }

    return fakes;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 0; i < n; i++) {
        int a,b;
        cin >> a >> b;
        a += MAXX/2;
        b += MAXX/2;
        cow[a][b] = true;

        cout << add(a,b) << endl;
    }
}
