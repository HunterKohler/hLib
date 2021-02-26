/*
ID: jhunter3
LANG: C++11
PROB: job
*/

// something to do "load balancing" idek
#include <iostream>
#include <tuple>

using namespace std;

#define MAXN 1000
#define MAXM 30
#define INF (1 << 30)

int n,m1,m2;
int a[MAXM],b[MAXM];
int a_f[MAXM] {};
int b_f[MAXM] {};
int tasks_a[MAXN] {};
int tasks_b[MAXN] {};

int main() {
    freopen("job.in", "r", stdin);
    freopen("job.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m1 >> m2;
    for(int i = 0; i < m1; i++)
        cin >> a[i];
    for(int i = 0; i < m2; i++)
        cin >> b[i];

    for(int i = 0; i < n; i++) {
        int min_t = INF;
        int k;
        for(int j = 0; j < m1; j++) {
            if(a_f[j] + a[j] < min_t) {
                min_t = a_f[j] + a[j];
                k = j;
            }
        }
        a_f[k] += a[k];
        tasks_a[i] = min_t;
    }

    for(int i = n-1; i >= 0; i--) {
        int min_t = INF;
        int k;
        // solving worst case?? for any indiv task??
        for(int j = 0; j < m2; j++) {
            if(b_f[j] + b[j] < min_t) {
                min_t = b_f[j] + b[j];
                k = j;
            }
        }
        b_f[k] += b[k];
        tasks_b[i] = min_t;
    }

    int max_ab = 0;
    for(int i = 0; i < n; i++)
        max_ab = max(max_ab, tasks_a[i] + tasks_b[i]);

    cout << tasks_a[n-1] << " " << max_ab << "\n";
}
