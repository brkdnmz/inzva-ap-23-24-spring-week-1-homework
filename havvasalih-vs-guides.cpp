#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 5; // max(y_i) + 1 (+5 actually, just to be safe :D)

class Solver {
    int n, k, q;
    vector<array<int, 2>> diff_ranges;
    vector<array<int, 2>> queries;

  public:
    Solver(int n, int k, int q, const vector<array<int, 2>> &diff_ranges, const vector<array<int, 2>> &queries)
        : n{n}, k{k}, q{q}, diff_ranges{diff_ranges}, queries{queries} {}

    /*
        Prefix sum
        O(N) (not n)

        Interval problems have their own trick.
        To find how many intervals cover any point, we preprocess the intervals.
        An interval [l, r] increments the coverage for all points from l to r.
        Its coverage starts from l, and ends at r.
        It looks like as follows:
            l-1 l  l+1 l+2 l+3 ... r-3 r-2 r-1 r  r+1 ...
            0   +1 +1  +1  +1      +1  +1  +1  +1 0   ...

        However, incrementing each of these one by one requires r-l+1 operations.
        The trick here is to only increment l and decrement r+1, and after all intervals are processed as so,
        calculate the prefix sum.
        Note that not r but r+1 should be decremented. It's because r is the last point that the range covers, i.e., r
        is also covered.

        Each element in the resulting array after increment-decrement (before prefix sum)
        tells us how many intervals start from there, and if it's negative, how many intervals ends at there.
        Of course, it's possible that x intervals start from and y intervals ends at the same point. If so, the value
        will be x - y.

        Can you see why this technique works?
    */
    void sol1() {
        // Not the best naming for negative values :D
        vector<int> n_ranges_starting_at(N);
        for (auto &[x, y] : diff_ranges) {
            n_ranges_starting_at[x]++;
            n_ranges_starting_at[y + 1]--;
        }

        vector<int> n_ranges_covering(N);
        for (int i = 1; i < N; i++) {
            n_ranges_covering[i] = n_ranges_covering[i - 1] + n_ranges_starting_at[i];
        }

        // Of course, this can also be filled in the upper for loop.
        // However, it's clearer this way, right?
        vector<bool> is_valid(N);
        for (int i = 1; i < N; i++) {
            is_valid[i] = n_ranges_covering[i] >= k;
        }
        // is_valid is such an unnecessary array, actually.
        // You may just use "n_ranges_covering[i] >= k".

        // Now, for answering queries fast, another prefix sum is needed.
        vector<int> n_valid_diffs(N);
        for (int i = 1; i < N; i++) {
            n_valid_diffs[i] = n_valid_diffs[i - 1] + is_valid[i];
        }

        for (auto &[l, r] : queries) {
            // l > 0, no danger here.
            cout << n_valid_diffs[r] - n_valid_diffs[l - 1] << "\n";
        }
    }

    /*
        Map + binary search
        O((n + q) * log(n))

        This solution is an overkill to the current problem.
        However, it doesn't depend on the constraint on y_i, which makes it powerful that it's capable of handling
        larger values.

        Failed to implement correctly :D
    */
    void sol2() {
        map<int, int> n_ranges_starting_at;
        for (auto &[x, y] : diff_ranges) {
            n_ranges_starting_at[x]++;
            n_ranges_starting_at[y + 1]--;
        }
        int starting_point = -1;
        int n_ranges_covering = 0;
        vector<array<int, 2>> valid_diff_ranges;
        for (auto &[point, cnt] : n_ranges_starting_at) {
            if (n_ranges_covering < k && n_ranges_covering + cnt >= k) {
                starting_point = point;
            } else if (n_ranges_covering >= k && n_ranges_covering + cnt < k) {
                valid_diff_ranges.push_back({starting_point, point - 1});
                starting_point = -1;
            }
            n_ranges_covering += cnt;
        }

        // Add the last range if exists.
        if (starting_point != -1) {
            valid_diff_ranges.push_back({starting_point, n_ranges_starting_at.rend()->second - 1});
        }

        // Note that valid_diff_ranges is already sorted, and ranges don't overlap (r_i < l_(i+1)).

        // Prefix sum.
        vector<int> total_range_len(1);
        for (auto &[l, r] : valid_diff_ranges) {
            total_range_len.push_back(total_range_len.back() + r - l + 1);
        }

        const int inf = 1e9 + 1;

        for (auto &[l, r] : queries) {
            // Want to find first valid range [l1, r1] such that l1 <= l <= r1.
            // Well, if it exists, the range after it starts after l. We can find that next range with upper_bound.
            int range_covering_l =
                upper_bound(valid_diff_ranges.begin(), valid_diff_ranges.end(), array<int, 2>{l, inf}) -
                valid_diff_ranges.begin() - 1;

            // Same logic as the previous.
            int range_covering_r =
                upper_bound(valid_diff_ranges.begin(), valid_diff_ranges.end(), array<int, 2>{r, inf}) -
                valid_diff_ranges.begin() - 1;

            // Handling a few cases...
            if (r < valid_diff_ranges.front()[0] || valid_diff_ranges.back()[1] < l) {
                cout << "0\n";
            } else if (range_covering_l == range_covering_r) {
                cout << min(r, valid_diff_ranges[range_covering_r][1]) - l + 1 << "\n";
            } else {
                // Add the subrange in the range covering l.
                int ans = range_covering_l == -1 ? 0 : valid_diff_ranges[range_covering_l][1] - l + 1;

                // Add the subrange in the range covering r.
                ans += valid_diff_ranges[range_covering_r][1] < r ? 0 : r - valid_diff_ranges[range_covering_r][0] + 1;

                // Add total range length in between, excluding the covering ranges.
                // Prefix sum array is 1-indexed!
                int first_range = range_covering_l == -1 ? 0 : range_covering_l + 1;
                int last_range =
                    valid_diff_ranges[range_covering_r][1] < r ? valid_diff_ranges.size() - 1 : range_covering_r - 1;
                ans += total_range_len[last_range + 1] - total_range_len[first_range];
                cout << ans << "\n";
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k, q;
    cin >> n >> k >> q;
    vector<array<int, 2>> diff_ranges(n);
    for (auto &[x, y] : diff_ranges)
        cin >> x >> y;
    vector<array<int, 2>> queries(q);
    for (auto &[l, r] : queries)
        cin >> l >> r;
    Solver solver(n, k, q, diff_ranges, queries);
    solver.sol1();
}