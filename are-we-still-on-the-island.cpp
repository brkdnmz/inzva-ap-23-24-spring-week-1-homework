#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    ll pre[n + 1] = {};
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        pre[i + 1] = pre[i] + a;
    }

    // sum(a_l..a_r)
    auto get_sum = [&](int l, int r) { return pre[r] - pre[l - 1]; };

    while (q--) {
        int l, r;
        cin >> l >> r;
        // Prefix sum is 1-indexed, no need for "l--, r--".

        /*
            Left sum = s_l = sum(l..k)
            Right sum = s_r = sum(k+1..r)

            Notice that the difference s_l - s_r increases as k increases. (*)
            It's because all a_i are positive.
            To minimize abs(s_l - s_r) requires making it as close to zero as possible.
            To get as close to zero as we can, we should seek for the smallest k that s_l - s_r >= 0.
            After that, the answer is the one between k and k-1 that leads to smaller absolute difference.
            In case of a tie, k-1 will be the target.

            Because of (*), the target k is binary searchable!
        */

        int lo = l, hi = r;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            ll left_sum = get_sum(l, mid);
            ll right_sum = get_sum(mid + 1, r);

            // We want the first k s.t. left_sum >= right_sum
            if (left_sum < right_sum) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        int target_k = lo;

        // Fun fact: the result will always be <= 1e9, hence, int is enough.
        // Not a necessary observation, though :D You may just use long long.
        int diff = get_sum(l, target_k) - get_sum(target_k + 1, r);

        // We check k-1 here.
        if (target_k > l) {
            // This difference will be at most 2e9 <= MAX_INT.
            // These observations are just for fun, not needed at all...
            int other_diff = get_sum(target_k, r) - get_sum(l, target_k - 1);

            if (other_diff <= diff)
                target_k--;
        }

        // Figure out why we didn't use (don't need) abs() at all :)

        cout << target_k << "\n";
    }
}