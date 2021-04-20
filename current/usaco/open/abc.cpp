#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void test_case();
int main() {
    freopen("abc.in","r",stdin);
    int T;
    cin >> T;
    for(int i = 0; i < T; i++)
        test_case();
}

int sub_cases(vector<int>&);
int sub_cases(vector<int>&,vector<int>&);
void test_case() {
    int n;
    cin >> n;
    vector<int> v(n);
    for(int& i: v)
        cin >> i;

    cout << n << ": " << sub_cases(v) << endl;
}

int sub_cases(vector<int>& v) {
    vector<int> u;
    return sub_cases(v,u);
}

bool is_possible(vector<int>&);
int sub_cases(vector<int>& v, vector<int>& order) {
    if(v.size() != order.size()) {
        int total = 0;

        for(int i: v) {
            bool has = false;
            for(int j: order) {
                has |= i == j;
            }

            if(!has) {
                order.push_back(i);
                total += sub_cases(v,order);
                order.pop_back();
            }
        }

        return total;
    } else {
        return is_possible(order) ? 1 : 0;
    }
}

bool is_possible(vector<int>& order) {
    if(order.size() == 7) {
        int a = order[0];
        int b = order[1];
        int c = order[2];
        int ab = order[3];
        int ac = order[4];
        int bc = order[5];
        int abc = order[6];

        return
            ab == a + b &&
            ac == a + c &&
            bc == b + c &&
            abc == a + b + c;
    }

    if(order.size() == 6) {
        int b = order[0];
        int c = order[1];
        int ab = order[2];
        int ac = order[3];
        int bc = order[4];
        int abc = order[5];
    }
}
