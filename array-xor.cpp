#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N_ADDICTS = 11;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    /*
        Fun fact: This is a prefix sum problem.
        Yes, it really is.
        The prefix sum we know uses the opposite of addition, that is, subtraction,
        in order to eliminate the "left part".

        Well, guess what? The opposite of XOR is also XOR itself :D
        That is, a XOR a = 0.
        // Refer to this wiki: https://en.wikipedia.org/wiki/Bitwise_operation
    */

    int n;
    cin >> n;
    int pre_xor[n + 1] = {};
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        pre_xor[i + 1] = pre_xor[i] ^ a;
    }
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        /*
            pre_xor[r] includes the elements in pre_xor[l - 1] once.
            When we XOR them, the elements up to l - 1 occur exactly twice, thus, they get cancel themselves
            What is left is a_l ^ a_(l+1) ^ ... ^ a_r.
        */

        // "<<" is also a bitwise operator that has a higher precedence than "^".
        // https://en.cppreference.com/w/cpp/language/operator_precedence
        // Thus, parentheses must be put.
        cout << (pre_xor[r] ^ pre_xor[l - 1]) << "\n";
    }
}