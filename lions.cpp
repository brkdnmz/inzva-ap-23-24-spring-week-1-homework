#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Solver {
    int n;
    int q;
    vector<int> lions;
    vector<array<int, 2>> queries;

  public:
    Solver(int n, int q, const vector<int> &lions, const vector<array<int, 2>> &queries)
        : n{n}, q{q}, lions{lions}, queries{queries} {}

    /*
        Sorting + binary search
        Using only the built-in lower_bound and upper_bound binary search functions.
        O((n + q) * log(n))
    */
    void sol1() {
        sort(lions.begin(), lions.end());
        for (auto &[l, r] : queries) {
            /*
                upper_bound(x) == Position of the first element > x
                Since our array is 0-indexed, the index values stand for the number of elements before each element.
                For example, there are 2 elements before the 2nd element.
                So, we can think of upper_bound as the number of elements <= x.
            */
            int n_lions_up_to_r = upper_bound(lions.begin(), lions.end(), r) - lions.begin();

            /*
                lower_bound(x) == Position of the first element >= x
                So, lower_bound(x) == # of elements < x
            */
            int n_lions_before_l = lower_bound(lions.begin(), lions.end(), l) - lions.begin();

            /*
                By the definitions, notice that (assuming we're dealing with integers):
                    lower_bound(x) == upper_bound(x - 1)
                    upper_bound(x) == lower_bound(x + 1)
                Try all four possible combinations to see if you get all green checks!
            */

            // Lions within [l, r] == Lions within [0, r] - Lions within [0, l-1]
            cout << n_lions_up_to_r - n_lions_before_l << "\n";
        }
    }

    /*
        Sorting + binary search
        Using our own binary search.
    */
    void sol2() {
        sort(lions.begin(), lions.end());

        // These below are lambda (a.k.a. inline) functions!

        // Index of the first lion >= l
        auto get_first_lion = [&](int l) {
            int lo = 0, hi = n;
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (lions[mid] >= l) {
                    // We want the leftmost lion -> Move hi to mid (mid might be the target)
                    hi = mid;
                } else {
                    // Target cannot be within [lo, mid] -> Move lo to mid + 1
                    lo = mid + 1;
                }
            }

            // If all lions are < l, then it returns n
            return lo;
        };

        // Index of the last lion <= r
        auto get_last_lion = [&](int r) {
            int lo = -1, hi = n - 1;
            while (lo < hi) {
                // +1 to avoid infinite loop for "lo = mid & hi = mid - 1" type of binary search.
                // May also write (lo + hi) / 2 + 1
                int mid = (lo + hi + 1) / 2;
                if (lions[mid] <= r) {
                    // We want the rightmost lion -> Move lo to mid (mid might be the target)
                    lo = mid;
                } else {
                    // Target cannot be within [mid, hi] -> Move hi to mid - 1
                    hi = mid - 1;
                }
            }

            // If all lions are > r, then it returns -1
            return lo;
        };

        /*
            Notice that get_last_lion(x) + 1 == get_first_lion(x + 1)!
            Don't think as a programmer, use your logic.

            Also, get_first_lion(l) == lower_bound(l)!

            Try to implement upper_bound(l) as well.
        */

        for (auto &[l, r] : queries) {
            int n_lions = get_last_lion(r) - get_first_lion(l) + 1;
            // n_lions is also equal to get_last_lion(r) - get_last_lion(l - 1).
            cout << n_lions << "\n";
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> lions(n);
    for (int &l : lions)
        cin >> l;
    vector<array<int, 2>> queries(q);
    for (auto &[l, r] : queries)
        cin >> l >> r;
    Solver solver(n, q, lions, queries);
    solver.sol1();
}