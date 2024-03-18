#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Solver {
    int n;
    int k;
    vector<int> days;

  public:
    Solver(int n, int k, const vector<int> &days) : n{n}, k{k}, days{days} {}

    void sol() {
        /*
            If a problem asks for the minimum/maximum of something,
            it's likely that binary search is applicable.

            Notice that if the max. hours can be H, it can also be H + 1.
            Similarly, if it can't be H, it can't also be H - 1.

            Well, this condition is both enough and required by itself for binary search.

            Also, these kind of problems have the common name:
                Binary searching the answer / Binary search for the answer
            Or, in Turkish: "Cevaba binary search" :D

            It's a bit of a "if you know, you know" situation, unfortunately.
            However, once you know, it becomes so fun to solve a problem with this technique by yourself!
        */

        // We define the boundaries by thinking how small/large the answer can be.
        // r can also be max(days), which can be found with *max_element(days.begin(), days.end())
        int l = 1, r = 1e9;
        while (l < r) {
            int mid = (l + r) / 2;
            /*
                When binary searching for the answer, the most crucial part is
                how to check whether mid could be a valid answer, i.e., the max. hours can be mid.

                The advantage is, this check can be done using mid itself, because we have it!

                For this problem, we can calculate the total operations required to make max. hours equal to mid.
            */

            ll total_operations_needed = 0;
            for (int hours : days) {
                // After x operations, there will be x + 1 days, where max. hours is mid.
                // Focus on the resulting x + 1 days. There should be as much "mid" as possible
                // to minimize total_operations_needed.
                // mid + mid + ... + mid + remainder == hours
                // The minimum number of the resulting days is ceil(hours / mid).
                // Thus, the number of operations is ceil(hours / mid) - 1.
                total_operations_needed += (hours + mid - 1) / mid - 1;

                // This also works, and might be more understandable:
                // total_operations_needed += hours / mid + (hours % mid > 0) - 1;

                // It turns out that (hours - 1) / mid also works.
            }

            if (total_operations_needed <= k) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }

        cout << l << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> days(n);
    for (int &d : days)
        cin >> d;
    Solver solver(n, k, days);
    solver.sol();
}