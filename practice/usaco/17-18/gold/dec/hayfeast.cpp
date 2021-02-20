#include <iostream>
#include <set>

using namespace std;
typedef long long ll;

#define MAXN 100000

ll n,m;
ll f[MAXN],s[MAXN];

int main() {
    freopen("hayfeast.in", "r", stdin);
    freopen("hayfeast.out", "w", stdout);

    scanf("%lld %lld",&n,&m);
    for(ll i = 0; i < n; i++) {
        scanf("%lld %lld",f + i, s + i);
    }

    ll min_s = (1ll << 60);

    ll sum = 0;
    multiset<ll> spices;

    ll i = 0, j = 0;

    while(i < n) {
        while(j < n && sum < m) {
            spices.insert(s[j]);
            sum += f[j++];
        }

        if(sum >= m) {
            min_s = min(min_s, *(--spices.end()));
        }

        spices.erase(spices.find(s[i]));
        sum -= f[i++];
    }

    printf("%lld", min_s);
}
