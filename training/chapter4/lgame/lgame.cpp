/*
ID: jhunter3
LANG: C++11
TASK: lgame
*/

#include <algorithm>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int factorial[] {1,1,2,6,24,120,720,5040};
int keyboard[] {2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};

int score(const string& s) {
    int total = 0;
    for(char c: s)
        total += keyboard[c - 'a'];
    return total;
}

string entry;
map<string,int> dict;

int max_mem[7];
int maximize(int i) {
    if(i >= entry.length())
        return 0;

    int& mem = max_mem[i];
    if(mem == -1) {
        for(int j = i + 1; j <= entry.length(); j++) {
            mem = max(mem,maximize(j) + dict.find(entry.substr(i,j-i))->second);
        }
    }

    return mem;
}

int main() {
    ifstream fin("lgame.in");
    ofstream fout("lgame.out");

    fin >> entry;

    ifstream din("lgame.dict");
    string temp;
    din >> temp;
    while(temp != ".") {
        dict[temp] = score(temp);
        din >> temp;
    }

    int max_all = 0;
    for(int i = 0; i < factorial[entry.length()]; i++) {
        for(int i =0 ; i < 7; i++)
            max_mem[i] = -1;

        max_all = max(max_all, maximize(0));
        next_permutation(entry.begin(),entry.end());
    }

    fout << max_all << endl;
}
