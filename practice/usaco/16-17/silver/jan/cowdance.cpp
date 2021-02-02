#include <iostream>
#include <queue>
#include <functional>

using namespace std;

#define MAXN 10000


int n,t_max;
int d[MAXN];
int main() {
    freopen("cowdance.in","r",stdin);
    freopen("cowdance.out","w",stdout);

    cin >> n >> t_max;
    for(int i = 0; i < n; i++)
        cin >> d[i];

    for(int k = 1; k <= n; k++) {
        priority_queue<int,vector<int>,greater<int>> q;
        for(int i = 0; i < k; i++)
            q.push(0);

        int t = 0,
            cow = 0;
        while(!q.empty()) {
            t = q.top();
            q.pop();

            if(cow < n)
                q.push(t + d[cow++]);
        }

        if(t <= t_max) {
            cout << k;
            return 0;
        }
    }
}
