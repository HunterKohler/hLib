/*
ID: jhunter3
LANG: C++11
TASK: lgame
*/

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <functional>

using namespace std;

#define np(s) next_permutation(s.begin(),s.end())

const hash<string> h;

const int VALS[] {2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};
const int FACT[] {1,1,2,6,24,120,720,5040};

int points(const string&);

vector<vector<int>> max_len_mem(5040+10,vector<int>(7+10,-1));
int max_len(int,int,const string&);

vector<tuple<int,int>> dict; // len <= 40000

ifstream fin("lgame.in");
ofstream fout("lgame.out");
int main() {
    string s;
    fin >> s;

    ifstream din("lgame.dict");
    string tmp;
    din >> tmp;
    while(tmp != ".") {
        int p;
        for(char c: tmp) {
            p += VALS[c - 'a'];
        }

        dict.emplace(h(tmp),p);
        din >> tmp;
    }

    sort(dict.begin(), dict.end());

    int max_l = -1;
    for(int i = 0; i < FACT[s.length()]; i++,np(s)) {
        max_l = max(max_l, max_len(i,0,s));
    }

    fout << max_l << endl;
}

int points(const string& s) {
    if(s.size() == 0) return 0;

    int index = (upper_bound(dict.begin(),dict.end(),s) - dict.begin())-1;

    if(index < s.size() && s == dict[index]) {
        return pvals[index];
    } else {
        return 0;
    }
}

int max_len(int permutation, int index, const string& s) {
    if(s.length() == 0)
        return 0;

    int& mem = max_len_mem[permutation][index];
    if(mem == -1) {
        for(int i = 1; i <= s.size(); i++) {
            mem = max(mem, points(s.substr(0,i)) + max_len(permutation,index+i, s.substr(i)));
        }
    }

    return mem;
}
