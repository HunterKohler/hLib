#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

#define MAXN 50000

int n;
int e[MAXN];
deque<int> b;
bool e_bool[2 * MAXN];
int main() {
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> e[i];
        e_bool[--e[i]] = true;
    }

    for(int i = 0, j = 0; i < n; i++) {
        while(e_bool[j])
            j++;
        b.push_back(j++);
    }

    sort(e, e + (n / 2), greater<int>());
    sort(e + (n / 2), e + n);

    int s = 0;
    for(int i = 0; i < n / 2; i++) {
        if(b.back() > e[i]) {
            b.pop_back();
            s++;
        }
    }

    while(b.size() > n / 2)
        b.pop_back();

    for(int i = n / 2; i < n; i++) {
        if(b.front() < e[i]) {
            b.pop_front();
            s++;
        }
    }

    cout << s;
}
