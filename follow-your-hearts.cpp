#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    /*
        Otis' distance   at time t =            o3 * t^3 + o2 * t^2 + o1 * t
        Maeve's distance at time t = m4 * t^4 + m3 * t^3 + m2 * t^2 + m1 * t
        Total distance   at time t = m4 * t^4 + (o3 + m3) * t^3 + ...

        In brief, the coefficients can be added up.
    */

    int d;
    cin >> d;
    int coef[4] = {}; // In this order: c4, c3, c2, c1
    for (int i = 1; i < 4; i++)
        cin >> coef[i];
    for (int i = 0; i < 4; i++) {
        int c;
        cin >> c;
        coef[i] += c;
    }

    /*
        So, we have a complex-enough polynomial that's strictly increasing thanks to positive coefficients.
        What we're looking for is the point that this polynomial equals d, that is, the initial distance between Otis
        and Maeve.

        Well, we have strictly increasing data and we're searching for particular point.
        The only difference is that the data is continuous unlike e.g. arrays.

        Guess what? This is still binary-searchable!
    */

    // Figure out how and why it works!
    auto dist = [&](double t) {
        double res = 0;
        for (int i = 0; i < 4; i++) {
            res = t * res + coef[i];
        }
        return res * t;
    };

    double l = 0, r = 1e3; // The answer can be at most 1e9^(1/4). No problem to use 1e3 instead!

    /*
        Binary searching continuous data is a bit different.
        We want to get as close to the target point as possible.
        Since l cannot ever be equal to r, we set a viable threshold instead.

        Another option is to use a fixed number of iterations: 100 to 200 should be enough.
        It's because after each iteration, the search space gets narrowed to half, and 100-200 halving is neat.
    */
    while (r - l > 1e-7) {
        double mid = (l + r) / 2;

        if (dist(mid) <= d) {
            l = mid;
        } else {
            r = mid;
        }

        // Yes, no +/- 1 there. It's continuous, baby!
    }

    cout << fixed << setprecision(2) << l << "\n";
}