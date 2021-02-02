#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    freopen("citystate.in","r",stdin);
    freopen("citystate.out","w",stdout);

    cin.ignore(10,'\n');

    int total = 0;
    unordered_map<string, int> umap;
    for(string c,s; cin >> c >> s;) {
        c = c.substr(0,2);

        if(c != s) {
            if(umap.count(c + s))
                umap[c + s]++;
            else
                umap.emplace(c + s, 1);

            if(umap.count(s + c))
                total += umap[s + c];
        }
    } cout << total;
}
