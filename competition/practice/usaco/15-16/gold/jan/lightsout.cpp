#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define MAXN 200

int n;
int x[MAXN], y[MAXN];

string& next(string& s, int i, int di) {
    int dx = x[(i+j+1) % n] - x[(i+j) % n];
    int dy = y[(i+j+1) % n] - y[(i+j) % n];

    if(dx > 0)
        s += 'E' + to_string(abs(dx));
    else if(dx < 0)
        s += 'W' + to_string(abs(dx));
    else if(dy > 0)
        s += 'N' + to_string(abs(dy));
    else if(dy < 0)
        s += 'S' + to_string(abs(dy));
}

int main() {
    freopen("lightsout.in", "r", stdin);
    freopen("lightsout.out", "w", stdout);

    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> x[i] >> y[i];

    map<string, vector<pair<int,int>>> seq;
    for(int i = 0; i < n; i++) {
        string s;
        for(int di = 0; di < n - 1; di++)
            seq[next(i,di,s)].emplace_back(i,di);
    }

    // for(auto& p: seq) {
    //     cout << p.first << ":" << endl;
    //     for(auto& q: p.second) {
    //         cout << "\t(" << q.first << "," << q.second << ")" << endl;
    //     }
    //     cout << endl;
    // }

    for(int i = 0; i < n; i++) {
        string s;
        for(int di = 0; di < n; di++) {
            next(s,i,di);
            if(seq[s].size() == 1) {
                
            }
        }
    }
}
