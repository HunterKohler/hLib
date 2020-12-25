#include <cstdio>
#include <iostream>

#define FOR(i,n) for(int (i) = 0; (i) < (n); (i)++)

using namespace std;

struct part {
    int length, speed;
};

int main() {
    freopen("speeding.in","r",stdin);
    freopen("speeding.out","w",stdout);
    ios_base::sync_with_stdio(false);

    int n,m;
    scanf("%d %d",&n,&m);

    part road[n], cow[m];
    FOR(i,n) scanf("%d %d",&road[i].length,&road[i].speed);
    FOR(i,m) scanf("%d %d",&cow[i].length,&cow[i].speed);

    int x{0}, y{0}, i{0}, j{0}, high{0};
    while(i < n && j < m) {
        // printf("%d %d %d %d\n",i,j,x,y);

        int x1 = x + road[i].length;
        int y1 = y + cow[j].length;

        if((y <= x && x <= y1) || (y <= x1 && x1 <= y1)) {
            high = max(high, cow[j].speed - road[i].speed);
        }

        if(x1 == y1) {
            x += road[i].length;
            y += cow[j].length;
            j++;
            i++;
        } else if(x1 < y1) {
            x += road[i].length;
            i++;
        } else {
            y += cow[j].length;
            j++;
        }
    }

    printf("%d\n",high);
}
