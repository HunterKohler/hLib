#include <array>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>


using namespace std;

constexpr int MAX_TEST_SIZE = 8;
constexpr int64_t MAX_PRIME = 1000000000ull;

void prime_search(vector<atomic_flag>& visited, vector<bool>& is_prime, int64_t start = 0) {
    for(int64_t i = start; i < MAX_PRIME; i++) {
        if(!visited[i].test_and_set()) {
            for(int64_t j = 1; j <= i; j++) {
                if(i % j == 0) {
                    is_prime[i] = false;
                    break;
                }
            }
        }
    }
}

void thread_test_helper(int n) {
    vector<bool> is_prime(MAX_PRIME);
    vector<atomic_flag> visited(MAX_PRIME);

    if(n == 1) {
        prime_search(visited, is_prime);
    } else {
        vector<thread> workers;

        for(int64_t i = 0; i < n; i++) {
            workers.emplace_back(prime_search,std::ref(visited), std::ref(is_prime), i * (MAX_PRIME / n));
        }

        for(int i = 0; i < n; i++) {
            workers[i].join();
        }
    }
}

#pragma region main

using hr_clock = chrono::high_resolution_clock;
using hr_timepoint = chrono::time_point<hr_clock>;

void thread_test(int n) {
    hr_timepoint start_time = hr_clock::now();
    thread_test_helper(n);
    hr_timepoint end_time = hr_clock::now();

    int64_t nsec = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    cout.setf(ios_base::fixed);
    cout.width(3);
    cout << "thread_test(" << n << ") | " << (nsec / 1e9) << " seconds\n";
}

int main() {
    cout << "thread::hardware_concurrency() -> "
         << thread::hardware_concurrency() << "\n\n";

    for(int n = 1; n <= MAX_TEST_SIZE; n *= 2) {
        thread_test(n);
    }
}

#pragma endregion

