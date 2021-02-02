#include <iostream>
#include <set>

using namespace std;

#define MAXN 100000

int n;
int h[MAXN];
multiset<int> l,r;

int main() {
    !freopen("bphoto.in", "r", stdin);
    !freopen("bphoto.out", "w", stdout);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> h[i];
        r.insert(h[i]);
    }

    for(int i = 0; i < n; i++) {

    }

}
