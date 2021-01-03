/*
ID: jhunter3
TASK: job
LANG: C++
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>

#define FOR(i,a,b) for(int (i) = (a); (i) < (b); (i)++)
#define FORN(i,n) FOR(i,0,n)
#define NMAX 1000
#define MMAX 30

using namespace std;

int N,M1,M2;
int A[MMAX], B[MMAX];

struct A_item {
    int i, m;
    int val() { return A[i] * m; }
};

int main() {
    freopen("job.in","r",stdin);
    freopen("job.out","w",stdout);
    ios_base::sync_with_stdio(false);

    scanf("%d %d %d",&N,&M1,&M2);
    FORN(i,M1) scanf("%d",&A[i]);
    FORN(i,M2) scanf("%d",&B[i]);

    sort(begin(A), begin(A) + M1);
    sort(begin(B), begin(B) + M2);

    auto comp = [](A_item &a, A_item &b) { return a.val() < b.val(); };
    vector<A_item> A_items;
    FORN(i,M1) FOR(m,1,N) A_items.push_back({i,m});
    sort(A_items.begin(), A_items.end(), comp);

    vector<int> A_times;
    FORN(i,N) A_times.push_back(A_items[i].val());
    int min_A = A_times[N - 1];

}
