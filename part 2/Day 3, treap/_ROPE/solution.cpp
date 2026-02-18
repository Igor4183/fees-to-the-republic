#include <bits/stdc++.h>
#include <ext/rope>
#define int int64_t

using namespace std;
using namespace __gnu_cxx;

int n, m;
rope<int> a;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    freopen("movetofront.in", "r", stdin);
    freopen("movetofront.out", "w", stdout);
    cin >> n >> m;

    for (int i = 1; i <= n; i++) a.push_back(i);

    while (m--) {
        int ql, qr;
        cin >> ql >> qr;
        rope<int> temp = a.substr(ql - 1, qr - ql + 1);
        a.erase(ql - 1, qr - ql + 1);
        a.insert(0, temp);
    }
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
}
