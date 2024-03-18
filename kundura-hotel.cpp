#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5;

class Solver {
    int n;
    vector<int> capacity;
    vector<int> guest;
    int q;
    vector<int> queries;

  public:
    Solver(int n, const vector<int> &capacity, const vector<int> &guest, int q, const vector<int> &queries)
        : n{n}, capacity{capacity}, guest{guest}, q{q}, queries{queries} {}

    /*
        Sorting + binary search
        O((n + q) * log(n))
    */
    void sol1() {
        vector<int> free_beds(n);
        for (int i = 0; i < n; i++) {
            free_beds[i] = capacity[i] - (i + 1 + guest[i]);
        }
        sort(free_beds.begin(), free_beds.end());
        for (auto &k : queries) {
            // # of rooms with free_beds >= k
            // Equal to n - (# of rooms with free_beds < k)
            // From the problem Lions, notice that lower_bound is usable!
            int unavailable_rooms = lower_bound(free_beds.begin(), free_beds.end(), k) - free_beds.begin();
            cout << n - unavailable_rooms << "\n";
        }
    }
    void sol1_alternative() {
        vector<int> free_beds(n);
        for (int i = 0; i < n; i++) {
            free_beds[i] = capacity[i] - (i + 1 + guest[i]);
        }

        // You can negate the array and use upper_bound!
        // Note that this solution is just for fun and to show possibilities :)
        for (int &f : free_beds)
            f = -f;
        sort(free_beds.begin(), free_beds.end());
        for (auto &k : queries) {
            // # of rooms with free_beds <= -k
            // From the problem Lions, notice that upper_bound is usable!
            int available_rooms = upper_bound(free_beds.begin(), free_beds.end(), -k) - free_beds.begin();
            cout << available_rooms << "\n";
        }
    }

    /*
        Prefix sum
        Using the low constraints to our advantage!
        Notice that any input <= 10^6
        O(N) (not n)
    */
    void sol2() {
        vector<int> free_beds(n);
        vector<int> rooms_with_at_most_free_beds(N);
        int invalid_rooms = 0; // Those with free_beds < 0
        for (int i = 0; i < n; i++) {
            free_beds[i] = capacity[i] - (i + 1 + guest[i]);
            // It's strange that this can be < 0...
            if (free_beds[i] >= 0)
                rooms_with_at_most_free_beds[free_beds[i]]++;
            else
                invalid_rooms++;
        }
        for (int i = 1; i < N; i++) {
            rooms_with_at_most_free_beds[i] += rooms_with_at_most_free_beds[i - 1];
        }
        for (auto &k : queries) {
            // Make sure to check k - 1 >= 0
            cout << n - invalid_rooms - (k ? rooms_with_at_most_free_beds[k - 1] : 0) << "\n";
        }
    }

    /*
        Suffix sum
        Very similar to the 2nd solution!
        O(N)
    */
    void sol3() {
        vector<int> free_beds(n);
        vector<int> rooms_with_at_least_free_beds(N); // Notice the change here!
        for (int i = 0; i < n; i++) {
            free_beds[i] = capacity[i] - (i + 1 + guest[i]);
            if (free_beds[i] >= 0)
                rooms_with_at_least_free_beds[free_beds[i]]++;
        }
        for (int i = N - 2; i >= 0; i--) {
            rooms_with_at_least_free_beds[i] += rooms_with_at_least_free_beds[i + 1];
        }
        for (auto &k : queries) {
            cout << rooms_with_at_least_free_beds[k] << "\n";
        }
    }

    /*
        Sorting + two pointers (one for queries, other for free_beds)
        Since queries don't affect other queries' answers (data won't be changed),
        we can also sort queries: Offline querying.
        O(n * log(n) + q * log(q))

        Note that this solution might be an overkill for this problem,
        but offline querying can be a quite powerful trick, and thus, it's good to know!
    */
    void sol4() {
        vector<int> free_beds(n);
        for (int i = 0; i < n; i++) {
            free_beds[i] = capacity[i] - (i + 1 + guest[i]);
        }
        sort(free_beds.begin(), free_beds.end());

        // Since the query order will get changed after sorting,
        // we should store the ids along with queries to answer in the right order.
        vector<array<int, 2>> qs_with_ids(q);
        for (int i = 0; i < q; i++) {
            qs_with_ids[i] = {queries[i], i};
        }
        sort(qs_with_ids.begin(), qs_with_ids.end());
        vector<int> answers(q);
        int last_invalid_room = -1;
        for (auto &[k, q_id] : qs_with_ids) {
            while (last_invalid_room + 1 < n && free_beds[last_invalid_room + 1] < k)
                last_invalid_room++;
            answers[q_id] = n - (last_invalid_room + 1);
        }
        for (int a : answers)
            cout << a << "\n";
    }
    void sol4_alternative() {
        vector<int> free_beds(n);
        for (int i = 0; i < n; i++) {
            free_beds[i] = capacity[i] - (i + 1 + guest[i]);
        }
        sort(free_beds.begin(), free_beds.end());
        reverse(free_beds.begin(), free_beds.end()); // Notice this.

        vector<array<int, 2>> qs_with_ids(q);
        for (int i = 0; i < q; i++) {
            qs_with_ids[i] = {queries[i], i};
        }
        sort(qs_with_ids.begin(), qs_with_ids.end());
        vector<int> answers(q);
        int last_valid_room = n - 1;
        for (auto &[k, q_id] : qs_with_ids) {
            while (last_valid_room >= 0 && free_beds[last_valid_room] < k)
                last_valid_room--;
            answers[q_id] = last_valid_room + 1;
        }
        for (int a : answers)
            cout << a << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> capacity(n), guest(n);
    for (int &c : capacity)
        cin >> c;
    for (int &g : guest)
        cin >> g;
    int q;
    cin >> q;
    vector<int> queries(q);
    for (int &k : queries)
        cin >> k;
    Solver solver(n, capacity, guest, q, queries);
    solver.sol1();
}