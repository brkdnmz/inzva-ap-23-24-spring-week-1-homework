#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Solver {
    int n;
    int m;
    vector<int> toasts;

  public:
    Solver(int n, int m, const vector<int> &toasts) : n{n}, m{m}, toasts{toasts} {}

    /*
        There's only one solution I know: binary search!
    */
    void sol() {
        /*
            If a problem asks for the minimum/maximum of something,
            it's likely that binary search is applicable.


            Notice that if the speed can be K, it can also be K + 1.
            Similarly, if it can't be K, it can't also be K - 1.

            Well, this condition is both enough and required by itself for binary search.

            Also, these kind of problems have the common name:
                Binary searching the answer / Binary search for the answer
            Or, in Turkish: "Cevaba binary search" :D

            It's a bit of a "if you know, you know" situation, unfortunately.
            However, once you know, it becomes so fun to solve a problem with this technique by yourself!
        */

        // We define the boundaries by thinking how small/large the answer can be.
        // r can also be max(toasts), which can be found with *max_element(toasts.begin(), toasts.end())
        int l = 1, r = 1e9;
        while (l < r) {
            int mid = (l + r) / 2;
            /*
                When binary searching for the answer, the most crucial part is
                how to check whether mid could be a valid answer, i.e., the toaster's speed can be mid.

                The advantage is, this check can be done using mid itself, because we have it!

                For this problem, we can calculate the total time required if toaster's speed is mid.
            */

            // Notice int isn't enough.
            // Actually, int is enough if we break the for loop
            // as soon as total_time_required exceeds k.
            ll total_time_required = 0;
            for (int t : toasts) {
                // We add ceil(t / mid).
                total_time_required += (t + mid - 1) / mid;
                // This also works, and might be more understandable:
                // total_time_required += t / mid + (t % mid > 0);
            }

            if (total_time_required <= m) {
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
    int n, m;
    cin >> n >> m;
    vector<int> toasts(n);
    for (int &t : toasts)
        cin >> t;
    Solver solver(n, m, toasts);
    solver.sol();
}