#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define MAXN 100000

inline bool d_equal(double a, double b) {
    return abs(b - a) < .00001;
}

int main() {
    freopen("homework.in","r",stdin);
    freopen("homework.out","w",stdout);

    int n, sum = 0;
    cin >> n;

    int v[MAXN],mins[MAXN];
    for(int i = 0; i < n; i++) {
        cin >> v[i];
        sum += v[i];
        mins[i] = i;
    }

    sort(mins,&mins[n],
        [&v](int i, int j) {
            return v[i] < v[j];
        });

    int at[MAXN];
    int i_mins = 0, i_at = 0;
    double _max = 0;
    for(int k = 0; k < n - 2; k++) {
        sum -= v[k];
        while(i_mins < k)
            i_mins++;

        double avg = (sum - v[mins[i_mins]]) / ((double) n - k - 2);
        if(d_equal(avg,_max)) {
            at[i_at] = k + 1;
            i_at++;
        } else if(avg > _max) {
            _max = avg;
            i_at = 1;
            at[0] = k + 1;
        }
    }

    for(int i = 0; i < i_at; i++)
        cout << at[i] << "\n";

}
