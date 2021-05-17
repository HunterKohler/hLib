#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

set<vector<int>> vis;

int max(vector<int> v) {
    if(v.size() == 1 || vis.count(v)) {
        return *max_element(v.begin(),v.end());
    } else {
        int m = *max_element(v.begin(),v.end());
        for(int i = 0; i < v.size() - 1;i++) {
            if(v[i] == v[i + 1]) {
                vector<int> u;
                for(int j = 0; j < v.size();j++) {
                    if(j != i) u.push_back((j == i + 1 ? 1 : 0) + v[j]);
                }
                m = max(m,max(u));
            }
        }
        return m;
    }
}

int main() {
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);

    int n;
    cin >> n;

    vector<int> v(n);
    for(int& i:v)
        cin >> i;

    cout << max(v);
}
