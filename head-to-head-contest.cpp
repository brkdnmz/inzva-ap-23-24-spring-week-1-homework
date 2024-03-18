#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Solver {
    int sum, n, x;

  public:
    Solver(int sum, int n, int x) : sum{sum}, n{n}, x{x} {}

    void sol() {
        /*
            If a problem asks for the minimum/maximum of something,
            it's likely that binary search is applicable.

            Notice that if the Doğukan can solve q problems, he can also solve q - 1.
            Similarly, if he can't solve q problems, he can't also solve q + 1.

            Well, this condition is both enough and required by itself for binary search.

            Also, these kind of problems have the common name:
                Binary searching the answer / Binary search for the answer
            Or, in Turkish: "Cevaba binary search" :D

            It's a bit of a "if you know, you know" situation, unfortunately.
            However, once you know, it becomes so fun to solve a problem with this technique by yourself!
        */

        /*
            Conditions:
                Each participant solves at least 1 problem.
                    ->  Subtract n from sum to guarantee this.
                The difference between the problem solved by consecutive participants can be at most 1.
                    ->  Think greedily. For Doğukan to solve as many problem as possible,
                        there should be a mountain/triangle-like shape.
        */

        sum -= n;

        // We define the boundaries by thinking how small/large the answer can be.
        // Note that everybody already solved 1 problem. We're searching for the extra.
        int l = 0, r = sum;
        while (l < r) {
            int mid = (l + r + 1) / 2; // +1 because of the type of the binary search
            /*
                When binary searching for the answer, the most crucial part is
                how to check whether mid could be a valid answer, i.e., the max. hours can be mid.

                The advantage is, this check can be done using mid itself, because we have it!

                For this problem, we can calculate the minimum number of problems needed to make Doğukan solve "mid"
               problems.
            */

            ll total_problems_needed = mid;

            int n_participants_left = x;
            int n_participants_right = n - 1 - x;

            // To have a triangular shape, we can use the Gaussian sum: mid-1 + mid-2 + mid-3 + ...
            auto gauss = [](int n) { return (ll)n * (n + 1) / 2; };

            /*
                The leftmost participant solves max(0, mid - n_participants_left) problems.
                The rightmost participant solves max(0, mid - n_participants_right) problems.
                Try to figure out the formulas below.
            */
            total_problems_needed += gauss(mid - 1) - gauss(max(0, mid - n_participants_left - 1));
            total_problems_needed += gauss(mid - 1) - gauss(max(0, mid - n_participants_right - 1));

            if (total_problems_needed <= sum) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }

        cout << 1 + l << "\n";
    }

    // I believe there's an O(1) solution that involves only math stuff, but I was too lazy to figure it out :D
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int sum, n, x;
    cin >> sum >> n >> x;
    Solver solver(sum, n, x);
    solver.sol();
}