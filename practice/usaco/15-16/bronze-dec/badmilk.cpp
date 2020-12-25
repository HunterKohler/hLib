#include <cstdio>
#include <iostream>
#include <unordered_set>
#include <vector>

#define FOR(i,n) for(int (i) = 0; (i) < (n); (i)++)

using namespace std;

struct drink {
    int m, t;
};

int main() {
    freopen("badmilk.in","r",stdin);
    freopen("badmilk.out","w",stdout);
    ios_base::sync_with_stdio(false);

    int N,M,D,S;
    scanf("%d %d %d %d",&N,&M,&D,&S);

    vector<drink> drinks[N];
    FOR(i,D) {
        int p,m,t;
        scanf("%d %d %d", &p, &m, &t); p--;
        drinks[p].push_back(drink{m,t});
    }

    unordered_set<int> safe;
    unordered_set<int> warn;
    FOR(i,S) {
        int p,t;
        scanf("%d %d", &p, &t); p--;
        for(drink d: drinks[p]) {
            if(d.t < t) {
                warn.insert(d.m);
                safe.erase(d.m);
            } else {
                safe.insert(d.m);
            }
        }
    }

    for(int i: safe) {
        warn.erase(i);
    }

    printf("%d",warn.size());
}
