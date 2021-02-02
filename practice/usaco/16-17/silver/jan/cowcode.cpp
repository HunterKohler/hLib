#include <iostream>
#include <string>
#include <cmath>

using namespace std;

typedef long long llong;

int main() {
    freopen("cowcode.in","r",stdin);
    freopen("cowcode.out","w",stdout);

    long long n;
    string s;
    cin >> s >> n;

    n--;
    long long len;
    while(n >= s.length()) {
        len = s.length();
        while(len << 1 <= n)
            len <<= 1;
        n -= (n == len) ? 1 : len + 1;
    }

    cout << s[n];
}
