#include <iostream>

using namespace std;

#define MAXN 50000

int n;  
int p[MAXN][2];

int main() {
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);

    // for(int *i: p)
    //     i[0] = i[1] = -1;

    // cout << p[11][1] << endl;

    cin >> n;
    for(int i = 0; i < 2 * n; i++) {
        int j;
        cin >> j;
        p[j - 1][0] = i;
        if(p[j - 1][0] > p[j - 1][1])
            swap(p[j - 1][0], p[j - 1][1]);
    }

    int t = 0;
    for(int i = 0; i < n; i++)
    for(int j = i + 1; j < n; j++) {
        int *a = p[i];
        int *b = p[j];

        // printf("(%d,%d) <-> (%d,%d)\n",a[0],a[1],b[0],b[1]);

        if(
            (a[0] < b[0] && b[0] < a[1] && a[1] < b[1]) ||
            (b[0] < a[0] && a[0] < b[1] && b[1] < a[1])
        ) t++;
    }

    cout << t;
}
