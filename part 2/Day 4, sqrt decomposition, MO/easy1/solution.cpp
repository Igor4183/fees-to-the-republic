#include <bits/stdc++.h>
#define int int64_t

using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);

    int n, m;
    cin >> n >> m;
    int c = sqrt(n);
    vector<int> a(n, 0);
    vector<int> b((n + c - 1) / c, 0);

    while (m--) {
        char t;
        cin >> t;
        if (t == 'A') {
            int idx, val;
            cin >> idx >> val;
            idx--;
            int old = a[idx];
            a[idx] = val;
            b[idx / c] += val - old;
        } else {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            int res = 0;
            while (l <= r) {
                if (l % c == 0 and l + c - 1 <= r) {
                    res += b[l / c];
                    l += c;
                } else {
                    res += a[l];
                    l++;
                }
            }
            cout << res << '\n';
        }
        // for (auto now : a) cout << now << ' ';
        // cout << endl;
        // for (auto now : b) cout << now << ' ';
        // cout << endl << endl;
    }
}
