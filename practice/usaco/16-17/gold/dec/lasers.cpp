#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define MAXN 100000

template <int* a>
struct comp {
    bool operator()(int i, int j) const {
        return a[i] < a[j];
    }
};

int n,x_l,y_l,x_b,y_b,s = 0,e = 1;
int x[MAXN],y[MAXN];

int main() {
    !freopen("lasers.in", "r", stdin);
    !freopen("lasers.out", "w", stdout);

    cin >> n >> x[0] >> y[0] >> x[1] >> y[1];
    for(int i = 2; i < n + 2; i++)
        cin >> x[i] >> y[i];
    n += 2;

    map<int,vector<int>,comp<x>> xmap;
    map<int,vector<int>,comp<y>> ymap;

    for(int i = 0; i < n; i++) {
        xmap[i].push_back(i);
        ymap[i].push_back(i);
    }

    queue<tuple<int,int>> q;
    q.push(s,-1);

    int i,l;
    while(!q.empty()) {
        tie(i,l) = q.top();
        q.pop();

        if(i == e)
            cout << d;

    }

    cout<<
}
