#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool broken[100000];
int main() {
    freopen("maxcross.in","r",stdin);
    freopen("maxcross.out","w",stdout);

    int n,k,b;
    cin >> n >> k >> b;

    for(int i; cin >> i;)
        broken[i - 1] = true;


    int off = count(&broken[0],&broken[k],true);
    int min_o = off;
    for(int i = k; i < n; i++) {
        if(broken[i - k])
            off--;
        if(broken[i])
            off++;
        min_o = min(min_o, off);
        if(min_o == 0)
            break;
    }

    cout << min_o;
}
