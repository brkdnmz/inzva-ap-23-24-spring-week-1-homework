#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Solver {
    int n;
    vector<int> temps;

  public:
    Solver(int n, const vector<int> &temps) : n{n}, temps{temps} {}

    /*
        Prefix sum + sorting
        O(n * log(n))
    */
    void sol1() {
        vector<ll> pre_sum(1, 0);
        for (int t : temps) {
            pre_sum.push_back(pre_sum.back() + t);
        }
        sort(pre_sum.begin(), pre_sum.end());
        int same_cnt = 1; // pre_sum[0]
        ll ans = 0;
        for (int i = 1; i < pre_sum.size(); i++) {
            if (pre_sum[i] == pre_sum[i - 1]) {
                // Add to the answer, the number of elements equal to the current.
                // Then, increment that number. (Post-increment)
                ans += same_cnt++;
            } else {
                // If the current element is different, reset the counter.
                same_cnt = 1;
            }
        }
        cout << ans << "\n";
    }
    void sol1_alternative() {
        vector<ll> pre_sum(1, 0);
        for (int t : temps) {
            pre_sum.push_back(pre_sum.back() + t);
        }
        sort(pre_sum.begin(), pre_sum.end());
        pre_sum.push_back(pre_sum.back() + 1); // To make line 49 execute for the last group
        int same_cnt = 1;
        ll ans = 0;
        for (int i = 1; i < pre_sum.size(); i++) {
            if (pre_sum[i] == pre_sum[i - 1]) {
                same_cnt++;
            } else {
                ans += (ll)same_cnt * (same_cnt - 1) / 2;
                same_cnt = 1;
            }
        }
        cout << ans << "\n";
    }

    /*
        Prefix sum + unordered_map
        O(n)

        Strong cases could lead to O(n^2) if many collisions occur in unordered_map,
        but that's not the case in algoleague :)
    */
    void sol2() {
        ll cur_pre_sum = 0;
        unordered_map<ll, int> pre_sum_cnt;
        pre_sum_cnt[cur_pre_sum]++;
        ll ans = 0;
        for (int t : temps) {
            // Yes, writing "cur_pre_sum += t" there is possible :D
            // You can think of "+=" as a function that adds the right-hand side to the left-hand side,
            // and return the resulting sum.
            ans += pre_sum_cnt[cur_pre_sum += t]++;
        }
        cout << ans << "\n";
    }
    void sol2_alternative() {
        ll cur_pre_sum = 0;
        unordered_map<ll, int> pre_sum_cnt;
        pre_sum_cnt[cur_pre_sum]++;
        ll ans = 0;
        for (int t : temps) {
            pre_sum_cnt[cur_pre_sum += t]++;
        }
        for (auto &[pre_sum, cnt] : pre_sum_cnt) {
            ans += (ll)cnt * (cnt - 1) / 2;
        }
        cout << ans << "\n";
    }

    /*
        Prefix sum + map
        O(n * log(n))
    */
    void sol3() {
        ll cur_pre_sum = 0;
        map<ll, int> pre_sum_cnt;
        pre_sum_cnt[cur_pre_sum]++;
        ll ans = 0;
        for (int t : temps) {
            ans += pre_sum_cnt[cur_pre_sum += t]++;
        }
        cout << ans << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> temps(n);
    for (int &t : temps)
        cin >> t;
    Solver solver(n, temps);
    solver.sol1();
}