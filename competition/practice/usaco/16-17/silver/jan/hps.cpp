#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    freopen("hps.in","r",stdin);
    freopen("hps.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    scanf("%d",&n);

    vector<vector<int>> v {{0},{0},{0}};
    unordered_map<char,vector<int>*> vmap {
        {'P', &v[0]},
        {'S', &v[1]},
        {'H', &v[2]}
    };

    char c;
    for(int i = 0 ; i < n; i++) {
        scanf(" %c",&c);
        for(vector<int>& u: v)
            u.push_back(u.back());
        vmap[c]->back()++;
    }

    int high = 0;
    for(int i = 1; i <= n; i++) {
        for(vector<int>& u: v)
        for(vector<int>& w: v) {
            high = max(
                high,
                u[i] + (w[n] - w[i])
            );
        }
    }

    printf("%d",high);
}
