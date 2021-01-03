#include <iostream>
#include <algorithm>
#include <vector>

struct cow {
    int a,b; bool h;
    cow(): h {false} {}
    bool operator<(const cow& x) const { return b < x.b; }
};

int main() {
    !freopen("helpcross.in","r",stdin);
    !freopen("helpcross.out","w",stdout);

    int c,n;
    std::cin >> c >> n;

    std::vector<int> t(c);
    for(int& i: t)
        std::cin >> i;
    std::sort(t.begin(),t.end());

    std::vector<cow> cows(n);
    for(cow& x: cows)
        std::cin >> x.a >> x.b;
    std::sort(cows.begin(),cows.end());

    int total = 0;
    for(int i: t)
    for(cow& x: cows)
        if(!x.h && x.a <= i && i <= x.b) {
            x.h = ++total;
            break;
        }
    std::cout << total;
}
