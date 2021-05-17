#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int t,a,b,m = 0;
bool vis[5000001];
queue<int> q1,q2;
int main() {
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);

    cin >> t >> a >> b;
    q1.push(0);
    while(!q1.empty()) {
        int n = q1.front();
        q1.pop();
        if(n <= t && !vis[n]) {
            vis[n] = true;
            m = max(m,n);
            q1.push(n + a);
            q1.push(n + b);
            q2.push(n / 2);
        }
    }

    fill_n(vis,t,false);
    while(!q2.empty()) {
        int n = q2.front();
        q2.pop();
        if(n <= t && !vis[n]) {
            vis[n] = true;
            m = max(m,n);
            q2.push(n + a);
            q2.push(n + b);
        }
    }

    cout << m;
}
